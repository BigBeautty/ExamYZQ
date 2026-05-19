#include "views/StackView.h"
#include "views/CardView.h"
#include "views/LayoutConstants.h"

USING_NS_CC;

namespace
{
    /** 备用牌堆起始 X（第一张牌的中心） */
    constexpr float kReserveStartX = 150.0f;
    /** 每张备用牌之间的水平偏移（产生重叠效果） */
    constexpr float kReserveOffsetX = 110.0f;
    /** 备用牌堆 Y 中心 */
    constexpr float kCardAreaY = 320.0f;
    /** 底牌区域中心 X */
    constexpr float kFoundationX = 750.0f;
    /** 回退按钮位置 */
    constexpr float kUndoX = 950.0f;
    constexpr float kUndoY = 80.0f;
}

StackView::StackView()
    : _reserveClickCallback(nullptr)
    , _undoClickCallback(nullptr)
    , _reserveNode(nullptr)
    , _foundationNode(nullptr)
    , _undoLabel(nullptr)
{
}

StackView* StackView::create()
{
    auto* view = new (std::nothrow) StackView();
    if (view && view->_init())
    {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool StackView::_init()
{
    if (!Node::init())
    {
        return false;
    }

    setContentSize(Size(LayoutConstants::kDesignWidth, LayoutConstants::kStackHeight));
    setAnchorPoint(Vec2::ZERO);

    auto* bg = LayerColor::create(
        Color4B::ORANGE, LayoutConstants::kDesignWidth, LayoutConstants::kStackHeight);
    addChild(bg, 0);

    _createReserveArea();
    _createFoundationArea();
    _createUndoButton();

    return true;
}

void StackView::setReserveClickCallback(const ReserveClickCallback& cb)
{
    _reserveClickCallback = cb;
}

void StackView::setUndoClickCallback(const UndoClickCallback& cb)
{
    _undoClickCallback = cb;
}

void StackView::_createReserveArea()
{
    _reserveNode = Node::create();
    _reserveNode->setPosition(Vec2::ZERO);
    _reserveNode->setAnchorPoint(Vec2::ZERO);
    _reserveNode->setContentSize(getContentSize());
    addChild(_reserveNode, 1);
}

void StackView::_createFoundationArea()
{
    _foundationNode = Node::create();
    _foundationNode->setPosition(Vec2(kFoundationX, kCardAreaY));
    _foundationNode->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(_foundationNode, 1);
}

void StackView::_createUndoButton()
{
    _undoLabel = Label::createWithSystemFont(u8"回退", "Arial", 48);
    _undoLabel->setPosition(Vec2(kUndoX, kUndoY));
    _undoLabel->setTextColor(Color4B::BLACK);
    addChild(_undoLabel, 2);

    auto* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event*) -> bool
    {
        Vec2 local = _undoLabel->convertToNodeSpace(touch->getLocation());
        Size size = _undoLabel->getContentSize();
        Rect rect(0, 0, size.width, size.height);
        return rect.containsPoint(local);
    };

    listener->onTouchEnded = [this](Touch*, Event*)
    {
        if (_undoClickCallback)
        {
            _undoClickCallback();
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _undoLabel);
}

void StackView::updateReserveDisplay(const std::vector<CardModel>& reserveCards)
{
    _reserveNode->removeAllChildren();

    for (int i = 0; i < static_cast<int>(reserveCards.size()); ++i)
    {
        auto* cardView = CardView::create(reserveCards[i]);
        if (!cardView)
        {
            continue;
        }

        float posX = kReserveStartX + i * kReserveOffsetX;
        cardView->setPosition(Vec2(posX, kCardAreaY));
        cardView->setClickable(true);

        int index = i;
        cardView->setClickCallback([this, index](int /*cardId*/)
        {
            if (_reserveClickCallback)
            {
                _reserveClickCallback(index);
            }
        });

        _reserveNode->addChild(cardView, i);
    }
}

void StackView::updateFoundationDisplay(const CardModel& topCard)
{
    _foundationNode->removeAllChildren();

    auto* cardView = CardView::create(topCard);
    if (cardView)
    {
        cardView->setPosition(Vec2::ZERO);
        cardView->setClickable(false);
        _foundationNode->addChild(cardView, 0);
    }
}

cocos2d::Vec2 StackView::getFoundationWorldPos(cocos2d::Node* coordSpace) const
{
    Vec2 worldPos = _foundationNode->getParent()->convertToWorldSpace(
        _foundationNode->getPosition());
    if (coordSpace)
    {
        return coordSpace->convertToNodeSpace(worldPos);
    }
    return worldPos;
}

void StackView::playFlipAnimation(const CardModel& flippedCard,
                                  float duration,
                                  const AnimationDoneCallback& onDone)
{
    auto* flying = CardView::create(flippedCard);
    if (!flying)
    {
        if (onDone) onDone();
        return;
    }
    flying->setClickable(false);

    int childCount = _reserveNode->getChildrenCount();
    float startX = kReserveStartX + childCount * kReserveOffsetX;
    flying->setPosition(Vec2(startX, kCardAreaY));
    addChild(flying, 10);

    Vec2 endPos = _foundationNode->getPosition();
    auto* move = MoveTo::create(duration, endPos);
    auto* done = CallFunc::create([flying, onDone]()
    {
        flying->removeFromParent();
        if (onDone) onDone();
    });
    flying->runAction(Sequence::create(move, done, nullptr));
}

void StackView::playUndoFlipAnimation(const CardModel& cardToReserve,
                                      float duration,
                                      const AnimationDoneCallback& onDone)
{
    auto* flying = CardView::create(cardToReserve);
    if (!flying)
    {
        if (onDone) onDone();
        return;
    }
    flying->setClickable(false);

    flying->setPosition(_foundationNode->getPosition());
    addChild(flying, 10);

    int childCount = _reserveNode->getChildrenCount();
    float endX = kReserveStartX + childCount * kReserveOffsetX;
    Vec2 endPos(endX, kCardAreaY);

    auto* move = MoveTo::create(duration, endPos);
    auto* done = CallFunc::create([flying, onDone]()
    {
        flying->removeFromParent();
        if (onDone) onDone();
    });
    flying->runAction(Sequence::create(move, done, nullptr));
}

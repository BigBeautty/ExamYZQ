#include "views/CardView.h"

USING_NS_CC;

namespace
{
    constexpr float kCornerMarginX = 22.0f;
    constexpr float kCornerMarginY = 22.0f;
}

CardView::CardView()
    : _cardId(-1)
    , _isClickable(false)
    , _clickCallback(nullptr)
{
}

CardView* CardView::create(const CardModel& model)
{
    auto* view = new (std::nothrow) CardView();
    if (view && view->_initWithModel(model))
    {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool CardView::_initWithModel(const CardModel& model)
{
    if (!Node::init())
    {
        return false;
    }

    _cardId = model.id;
    _isClickable = true;

    setAnchorPoint(Vec2(0.5f, 0.5f));
    ignoreAnchorPointForPosition(false);

    // 牌底板
    auto* baseSprite = Sprite::create("res/card_general.png");
    if (baseSprite)
    {
        const auto baseSize = baseSprite->getContentSize();
        setContentSize(baseSize);
        baseSprite->setPosition(Vec2(baseSize.width * 0.5f, baseSize.height * 0.5f));
        addChild(baseSprite, 0);
    }

    const auto cardSize = getContentSize();
    const float w = cardSize.width;
    const float h = cardSize.height;
    const bool isRed = model.isRedSuit();

    // 大数字（牌中心）
    auto* bigNum = Sprite::create(_getBigNumberImagePath(model.cardFace, isRed));
    if (bigNum)
    {
        bigNum->setPosition(Vec2(w * 0.5f, h * 0.5f));
        addChild(bigNum, 1);
    }

    // 小数字（左上角）
    auto* smallNum = Sprite::create(_getSmallNumberImagePath(model.cardFace, isRed));
    if (smallNum)
    {
        smallNum->setAnchorPoint(Vec2(0.0f, 1.0f));
        smallNum->setPosition(Vec2(kCornerMarginX, h - kCornerMarginY));
        addChild(smallNum, 2);
    }

    // 花色（右上角）
    auto* suitSprite = Sprite::create(_getSuitImagePath(model.cardSuit));
    if (suitSprite)
    {
        suitSprite->setAnchorPoint(Vec2(1.0f, 1.0f));
        suitSprite->setPosition(Vec2(w - kCornerMarginX, h - kCornerMarginY));
        addChild(suitSprite, 2);
    }

    _setupTouchListener();
    return true;
}

void CardView::_setupTouchListener()
{
    auto* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event*) -> bool
    {
        if (!_isClickable)
        {
            return false;
        }
        const Vec2 local = convertToNodeSpace(touch->getLocation());
        const Size size = getContentSize();
        const Rect rect(0, 0, size.width, size.height);
        return rect.containsPoint(local);
    };

    listener->onTouchEnded = [this](Touch*, Event*)
    {
        if (_isClickable && _clickCallback)
        {
            _clickCallback(_cardId);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CardView::setClickCallback(const ClickCallback& cb)
{
    _clickCallback = cb;
}

void CardView::setClickable(bool clickable)
{
    _isClickable = clickable;
    setOpacity(clickable ? 255 : 150);
}

int CardView::getCardId() const
{
    return _cardId;
}

std::string CardView::_getSuitImagePath(int suit) const
{
    switch (suit)
    {
    case 0: return "res/suits/club.png";
    case 1: return "res/suits/diamond.png";
    case 2: return "res/suits/heart.png";
    case 3: return "res/suits/spade.png";
    default: return "res/suits/club.png";
    }
}

std::string CardView::_getBigNumberImagePath(int face, bool isRed) const
{
    const std::string color = isRed ? "red" : "black";
    return "res/number/big_" + color + "_" + _faceToString(face) + ".png";
}

std::string CardView::_getSmallNumberImagePath(int face, bool isRed) const
{
    const std::string color = isRed ? "red" : "black";
    return "res/number/small_" + color + "_" + _faceToString(face) + ".png";
}

std::string CardView::_faceToString(int face) const
{
    switch (face)
    {
    case 0:  return "A";
    case 1:  return "2";
    case 2:  return "3";
    case 3:  return "4";
    case 4:  return "5";
    case 5:  return "6";
    case 6:  return "7";
    case 7:  return "8";
    case 8:  return "9";
    case 9:  return "10";
    case 10: return "J";
    case 11: return "Q";
    case 12: return "K";
    default: return "A";
    }
}

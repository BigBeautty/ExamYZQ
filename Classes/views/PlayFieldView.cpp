#include "views/PlayFieldView.h"
#include "views/LayoutConstants.h"

USING_NS_CC;

PlayFieldView* PlayFieldView::create()
{
    auto* view = new (std::nothrow) PlayFieldView();
    if (view && view->_init())
    {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool PlayFieldView::_init()
{
    if (!Node::init())
    {
        return false;
    }

    setContentSize(Size(LayoutConstants::kDesignWidth,
                        LayoutConstants::kPlayfieldHeight));

    auto* bg = LayerColor::create(
        Color4B::GRAY,
        LayoutConstants::kDesignWidth,
        LayoutConstants::kPlayfieldHeight);
    addChild(bg, -1);

    return true;
}

void PlayFieldView::setupCards(const std::vector<CardModel>& cards)
{
    for (auto& pair : _cardViews)
    {
        if (pair.second)
        {
            pair.second->removeFromParent();
        }
    }
    _cardViews.clear();

    for (const auto& card : cards)
    {
        auto* cardView = CardView::create(card);
        if (!cardView)
        {
            continue;
        }
        cardView->setPosition(card.position);
        cardView->setClickCallback(_cardClickCallback);
        cardView->setClickable(true);
        addChild(cardView);
        _cardViews[card.id] = cardView;
    }
}

void PlayFieldView::setCardClickCallback(const CardClickCallback& cb)
{
    _cardClickCallback = cb;
    for (auto& pair : _cardViews)
    {
        if (pair.second)
        {
            pair.second->setClickCallback(cb);
        }
    }
}

void PlayFieldView::restoreCardView(const CardModel& card)
{
    auto* cardView = CardView::create(card);
    if (!cardView)
    {
        return;
    }
    cardView->setPosition(card.position);
    cardView->setClickCallback(_cardClickCallback);
    cardView->setClickable(true);
    addChild(cardView);
    _cardViews[card.id] = cardView;
}

cocos2d::Node* PlayFieldView::extractCardView(int cardId)
{
    auto it = _cardViews.find(cardId);
    if (it == _cardViews.end() || !it->second)
    {
        return nullptr;
    }
    auto* cardView = it->second;
    _cardViews.erase(it);

    cardView->setClickable(false);
    cardView->retain();
    cardView->removeFromParent();
    return cardView;
}

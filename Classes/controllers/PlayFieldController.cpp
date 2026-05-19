#include "controllers/PlayFieldController.h"
#include "cocos2d.h"

USING_NS_CC;

PlayFieldController::PlayFieldController()
    : _view(nullptr)
    , _matchCallback(nullptr)
    , _requestMatchCallback(nullptr)
{
}

PlayFieldController::~PlayFieldController()
{
}

void PlayFieldController::init(const std::vector<CardModel>& cards)
{
    _model.init(cards);

    _view = PlayFieldView::create();
    if (_view)
    {
        _view->setCardClickCallback(
            [this](int cardId)
            {
                _onCardClicked(cardId);
            });
        _view->setupCards(cards);
    }
}

void PlayFieldController::setMatchCallback(const MatchCallback& cb)
{
    _matchCallback = cb;
}

void PlayFieldController::setRequestMatchCallback(const RequestMatchCallback& cb)
{
    _requestMatchCallback = cb;
}

void PlayFieldController::_onCardClicked(int cardId)
{
    if (_requestMatchCallback)
    {
        _requestMatchCallback(cardId);
    }
}

void PlayFieldController::tryMatch(int cardId, const CardModel& foundationTop)
{
    const auto& cards = _model.getCards();
    if (cardId < 0 || cardId >= static_cast<int>(cards.size()))
    {
        return;
    }
    const CardModel clickedCard = cards[cardId];

    if (!clickedCard.canMatch(foundationTop))
    {
        return;
    }

    _model.removeCard(cardId);

    Node* extracted = _view ? _view->extractCardView(cardId) : nullptr;

    if (_matchCallback)
    {
        _matchCallback(clickedCard, extracted);
    }
    else if (extracted)
    {
        extracted->release();
    }
}

void PlayFieldController::restoreCard(const CardModel& card)
{
    _model.restoreCard(card);
    if (_view)
    {
        _view->restoreCardView(card);
    }
}

PlayFieldView* PlayFieldController::getView() const
{
    return _view;
}

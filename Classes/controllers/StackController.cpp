#include "controllers/StackController.h"
#include "cocos2d.h"

USING_NS_CC;

namespace
{
    constexpr float kFlipAnimDuration = 0.35f;
}

StackController::StackController()
    : _view(nullptr)
    , _flipCallback(nullptr)
    , _undoCallback(nullptr)
{
}

StackController::~StackController()
{
}

void StackController::init(const std::vector<CardModel>& stackCards)
{
    _model.init(stackCards);
    _view = StackView::create();

    refreshFoundationView();
    refreshReserveView();

    _view->setReserveClickCallback(
        [this](int index)
        {
            _onReserveClicked(index);
        });

    _view->setUndoClickCallback(
        [this]()
        {
            if (_undoCallback)
            {
                _undoCallback();
            }
        });
}

void StackController::setFlipCallback(const FlipCallback& cb)
{
    _flipCallback = cb;
}

void StackController::setUndoCallback(const UndoCallback& cb)
{
    _undoCallback = cb;
}

void StackController::_onReserveClicked(int /*index*/)
{
    if (_model.isReserveEmpty())
    {
        return;
    }

    CardModel flippedCard = _model.flipFromReserve();

    refreshReserveView();

    auto* self = this;
    auto card = flippedCard;
    _view->playFlipAnimation(flippedCard, kFlipAnimDuration,
        [self, card]()
        {
            self->refreshFoundationView();
            if (self->_flipCallback)
            {
                self->_flipCallback(card);
            }
        });
}

void StackController::pushToFoundation(const CardModel& card)
{
    _model.pushToFoundation(card);
    refreshFoundationView();
}

CardModel StackController::popFromFoundation()
{
    CardModel card = _model.popFromFoundation();
    refreshFoundationView();
    return card;
}

void StackController::pushToReserve(const CardModel& card)
{
    _model.pushToReserve(card);
    refreshReserveView();
}

const CardModel& StackController::getTopFoundation() const
{
    return _model.getTopFoundation();
}

StackView* StackController::getView() const
{
    return _view;
}

void StackController::refreshFoundationView()
{
    if (_model.getFoundationSize() > 0)
    {
        _view->updateFoundationDisplay(_model.getTopFoundation());
    }
}

void StackController::refreshReserveView()
{
    _view->updateReserveDisplay(_model.getReserveCards());
}

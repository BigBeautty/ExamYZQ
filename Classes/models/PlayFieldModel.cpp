#include "models/PlayFieldModel.h"

void PlayFieldModel::init(const std::vector<CardModel>& cards)
{
    _cards = cards;
    _removed.assign(cards.size(), false);
}

const std::vector<CardModel>& PlayFieldModel::getCards() const
{
    return _cards;
}

void PlayFieldModel::removeCard(int cardId)
{
    if (cardId < 0 || cardId >= static_cast<int>(_removed.size()))
    {
        return;
    }
    _removed[cardId] = true;
}

void PlayFieldModel::restoreCard(const CardModel& card)
{
    int cardId = card.id;
    if (cardId < 0 || cardId >= static_cast<int>(_removed.size()))
    {
        return;
    }
    _removed[cardId] = false;
}

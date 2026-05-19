#include "models/CardModel.h"
#include <cstdlib>

bool CardModel::canMatch(const CardModel& other) const
{
    int diff = std::abs(cardFace - other.cardFace);
    return diff == 1;
}

bool CardModel::isRedSuit() const
{
    // diamond(1) 和 heart(2) 为红色花色
    return cardSuit == 1 || cardSuit == 2;
}

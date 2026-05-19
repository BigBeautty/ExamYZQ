#include "models/StackModel.h"

void StackModel::init(const std::vector<CardModel>& stackCards)
{
    _reserve.clear();
    _foundation.clear();

    if (stackCards.empty())
    {
        return;
    }

    // 最后一个元素作为初始底牌放入 _foundation
    _foundation.push_back(stackCards.back());

    // 其余元素按顺序放入 _reserve
    for (size_t i = 0; i < stackCards.size() - 1; ++i)
    {
        _reserve.push_back(stackCards[i]);
    }
}

CardModel StackModel::flipFromReserve()
{
    // 从备用牌堆顶部（back）取出一张牌
    CardModel card = _reserve.back();
    _reserve.pop_back();

    // 压入底牌堆顶部
    _foundation.push_back(card);

    return card;
}

void StackModel::pushToFoundation(const CardModel& card)
{
    _foundation.push_back(card);
}

CardModel StackModel::popFromFoundation()
{
    CardModel card = _foundation.back();
    _foundation.pop_back();
    return card;
}

void StackModel::pushToReserve(const CardModel& card)
{
    _reserve.push_back(card);
}

const CardModel& StackModel::getTopFoundation() const
{
    return _foundation.back();
}

bool StackModel::isReserveEmpty() const
{
    return _reserve.empty();
}

int StackModel::getReserveSize() const
{
    return static_cast<int>(_reserve.size());
}

int StackModel::getFoundationSize() const
{
    return static_cast<int>(_foundation.size());
}

const std::vector<CardModel>& StackModel::getReserveCards() const
{
    return _reserve;
}

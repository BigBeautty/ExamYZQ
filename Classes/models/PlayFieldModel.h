#pragma once

#include <vector>
#include "models/CardModel.h"

/**
 * @brief 主牌区数据模型
 *
 * 管理所有主牌区的 CardModel，支持移除和恢复操作。
 */
class PlayFieldModel
{
public:
    /**
     * @brief 初始化主牌区
     * @param cards 主牌区所有牌面数据
     */
    void init(const std::vector<CardModel>& cards);

    /**
     * @brief 获取所有牌
     * @return 当前主牌区牌面列表的常量引用
     */
    const std::vector<CardModel>& getCards() const;

    /**
     * @brief 移除指定牌
     * @param cardId 要移除的牌的 ID
     */
    void removeCard(int cardId);

    /**
     * @brief 恢复指定牌到原位置（回退用）
     * @param card 要恢复的牌数据
     */
    void restoreCard(const CardModel& card);

private:
    /** 主牌区所有牌面数据 */
    std::vector<CardModel> _cards;

    /** 已移除的牌标记 */
    std::vector<bool> _removed;
};



#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
#include "views/CardView.h"
#include <vector>
#include <functional>
#include <unordered_map>

/**
 * @brief 主牌区视图
 *
 * 负责在 1080x1500 的区域内显示所有主牌区的牌面，
 * 管理 CardView 的创建、提取（用于飞行动画）和恢复。
 */
class PlayFieldView : public cocos2d::Node
{
public:
    /** 牌点击回调类型 */
    using CardClickCallback = std::function<void(int cardId)>;

    /** 工厂方法，创建 PlayFieldView 实例 */
    static PlayFieldView* create();

    /**
     * @brief 根据 CardModel 列表创建并显示所有 CardView
     * @param cards 主牌区牌面数据
     */
    void setupCards(const std::vector<CardModel>& cards);

    /**
     * @brief 设置牌点击回调
     * @param cb 点击时调用的回调函数
     */
    void setCardClickCallback(const CardClickCallback& cb);

    /**
     * @brief 恢复指定牌的视图到正确位置
     * @param card 要恢复的牌数据
     */
    void restoreCardView(const CardModel& card);

    /**
     * @brief 把指定 cardId 的 CardView 从映射和父节点中分离并返回
     *
     * 返回的指针已 retain 一次，调用方接管所有权。
     *
     * @param cardId 要分离的牌 ID
     * @return 该 CardView 的 Node 指针；找不到返回 nullptr
     */
    cocos2d::Node* extractCardView(int cardId);

private:
    /** 初始化方法 */
    bool _init();

    /** 牌点击回调 */
    CardClickCallback _cardClickCallback;

    /** cardId 到 CardView 的映射 */
    std::unordered_map<int, CardView*> _cardViews;
};



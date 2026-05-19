#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
#include <functional>
#include <vector>

class CardView;

/**
 * @brief 堆牌区视图
 *
 * 显示备用牌堆（左侧，所有牌正面水平排列，有重叠偏移）、
 * 当前底牌（右侧，只显示最上面一张）和回退按钮（右下角）。
 * 通过回调将用户点击事件传递给 StackController。
 */
class StackView : public cocos2d::Node
{
public:
    /** 备用牌堆中某张牌被点击的回调，参数为该牌在备用牌堆中的索引 */
    using ReserveClickCallback = std::function<void(int index)>;

    /** 回退按钮点击回调 */
    using UndoClickCallback = std::function<void()>;

    /** 通用动画完成回调 */
    using AnimationDoneCallback = std::function<void()>;

    /** 工厂方法 */
    static StackView* create();

    /**
     * @brief 设置备用牌堆点击回调
     * @param cb 点击时调用的回调函数
     */
    void setReserveClickCallback(const ReserveClickCallback& cb);

    /**
     * @brief 设置回退按钮点击回调
     * @param cb 点击时调用的回调函数
     */
    void setUndoClickCallback(const UndoClickCallback& cb);

    /**
     * @brief 用真实 CardView 水平排列显示所有备用牌
     * @param reserveCards 备用牌堆数据
     */
    void updateReserveDisplay(const std::vector<CardModel>& reserveCards);

    /**
     * @brief 立刻把底牌区的 CardView 替换为指定牌（无动画）
     * @param topCard 新的底牌数据
     */
    void updateFoundationDisplay(const CardModel& topCard);

    /**
     * @brief 获取底牌区中心在指定坐标空间中的位置
     * @param coordSpace 目标坐标空间节点
     * @return 底牌区中心位置
     */
    cocos2d::Vec2 getFoundationWorldPos(cocos2d::Node* coordSpace) const;

    /**
     * @brief 播放备用牌堆最右侧 -> 底牌的翻牌动画
     * @param flippedCard 翻出的牌数据
     * @param duration 动画时长（秒）
     * @param onDone 动画完成回调
     */
    void playFlipAnimation(const CardModel& flippedCard,
                           float duration,
                           const AnimationDoneCallback& onDone);

    /**
     * @brief 播放底牌 -> 备用牌堆最右侧的回退翻牌动画
     * @param cardToReserve 要放回的牌数据
     * @param duration 动画时长（秒）
     * @param onDone 动画完成回调
     */
    void playUndoFlipAnimation(const CardModel& cardToReserve,
                               float duration,
                               const AnimationDoneCallback& onDone);

private:
    StackView();
    bool _init();

    void _createReserveArea();
    void _createFoundationArea();
    void _createUndoButton();

    ReserveClickCallback _reserveClickCallback;   ///< 备用牌堆点击回调
    UndoClickCallback _undoClickCallback;         ///< 回退按钮点击回调

    cocos2d::Node* _reserveNode;       ///< 备用牌堆容器
    cocos2d::Node* _foundationNode;    ///< 底牌显示容器
    cocos2d::Label* _undoLabel;        ///< 回退按钮
};

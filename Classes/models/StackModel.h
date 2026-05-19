#pragma once

#include <vector>
#include "models/CardModel.h"

/**
 * @brief 堆牌区数据模型，管理备用牌堆和底牌堆
 *
 * 备用牌堆(reserve)存放待翻的牌，底牌堆(foundation)存放当前底牌。
 * 玩家可从备用牌堆翻牌到底牌堆，也可通过回退操作恢复状态。
 */
class StackModel
{
public:
    /**
     * @brief 初始化堆牌区
     *
     * 传入的 stackCards 中，最后一个元素作为初始底牌放入 _foundation，
     * 其余元素按顺序放入 _reserve。
     *
     * @param stackCards 堆牌区所有牌面数据
     */
    void init(const std::vector<CardModel>& stackCards);

    /**
     * @brief 从备用牌堆顶部翻一张牌到底牌堆
     *
     * 取出备用牌堆顶部（back）的牌，压入底牌堆顶部。
     *
     * @return 翻出的牌
     */
    CardModel flipFromReserve();

    /**
     * @brief 将一张牌压入底牌堆顶部
     *
     * @param card 要压入的牌
     */
    void pushToFoundation(const CardModel& card);

    /**
     * @brief 从底牌堆顶部弹出一张牌（回退用）
     *
     * @return 弹出的牌
     */
    CardModel popFromFoundation();

    /**
     * @brief 将一张牌放回备用牌堆顶部（回退用）
     *
     * @param card 要放回的牌
     */
    void pushToReserve(const CardModel& card);

    /**
     * @brief 获取当前底牌（底牌堆顶部）
     *
     * @return 底牌堆顶部牌的常量引用
     */
    const CardModel& getTopFoundation() const;

    /**
     * @brief 判断备用牌堆是否为空
     *
     * @return true 备用牌堆为空，false 备用牌堆非空
     */
    bool isReserveEmpty() const;

    /**
     * @brief 获取备用牌堆大小
     *
     * @return 备用牌堆中的牌数
     */
    int getReserveSize() const;

    /**
     * @brief 获取底牌堆大小
     *
     * @return 底牌堆中的牌数
     */
    int getFoundationSize() const;

    /**
     * @brief 获取备用牌堆所有牌数据（供 View 显示用）
     *
     * @return 备用牌堆的常量引用
     */
    const std::vector<CardModel>& getReserveCards() const;

private:
    /** 备用牌堆，顶部为 back() */
    std::vector<CardModel> _reserve;

    /** 底牌堆，顶部为 back() */
    std::vector<CardModel> _foundation;
};



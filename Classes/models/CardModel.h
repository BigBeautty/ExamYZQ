#pragma once

#include "cocos2d.h"

/**
 * @brief 单张牌的数据模型
 *
 * 存储牌面数字、花色、位置坐标等信息，
 * 并提供匹配判断和花色查询方法。
 */
struct CardModel
{
    /** 牌面数字，取值 0-12（A=0, 2=1, ..., 10=9, J=10, Q=11, K=12） */
    int cardFace;

    /** 花色，取值 0-3（club=0, diamond=1, heart=2, spade=3） */
    int cardSuit;

    /** 在牌区中的位置坐标 */
    cocos2d::Vec2 position;

    /** 唯一标识符 */
    int id;

    /**
     * @brief 判断是否能与目标牌匹配
     *
     * 匹配规则：两张牌的 cardFace 差值绝对值为 1。
     * 边界处理：A(0) 仅匹配 2(1)，K(12) 仅匹配 Q(11)，不循环。
     *
     * @param other 目标牌
     * @return true 可以匹配，false 不可匹配
     */
    bool canMatch(const CardModel& other) const;

    /**
     * @brief 判断花色是否为红色
     *
     * diamond(1) 和 heart(2) 为红色花色。
     *
     * @return true 红色花色，false 黑色花色
     */
    bool isRedSuit() const;
};



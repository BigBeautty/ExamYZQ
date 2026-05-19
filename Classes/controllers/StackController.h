#pragma once

#include <functional>
#include <vector>
#include "models/StackModel.h"
#include "views/StackView.h"

/**
 * @brief 堆牌区控制器
 *
 * 管理备用牌堆和底牌堆的交互逻辑，协调 StackModel 与 StackView。
 * 通过回调通知 GameController 翻牌事件和回退请求。
 */
class StackController
{
public:
    /** 翻牌成功回调：通知 GameController 翻出的牌 */
    using FlipCallback = std::function<void(const CardModel&)>;

    /** 回退按钮回调：通知 GameController 执行回退 */
    using UndoCallback = std::function<void()>;

    StackController();
    ~StackController();

    /**
     * @brief 初始化堆牌区
     * @param stackCards 堆牌区所有牌面数据（最后一个为初始底牌）
     */
    void init(const std::vector<CardModel>& stackCards);

    /**
     * @brief 设置翻牌回调
     * @param cb 翻牌成功时调用的回调函数
     */
    void setFlipCallback(const FlipCallback& cb);

    /**
     * @brief 设置回退按钮回调
     * @param cb 回退按钮点击时调用的回调函数
     */
    void setUndoCallback(const UndoCallback& cb);

    /**
     * @brief 把外部传入的牌压入底牌堆（匹配流程用）
     * @param card 要压入的牌
     */
    void pushToFoundation(const CardModel& card);

    /**
     * @brief 弹出底牌堆顶牌（回退用）
     * @return 弹出的牌
     */
    CardModel popFromFoundation();

    /**
     * @brief 把牌放回备用牌堆顶部（回退用）
     * @param card 要放回的牌
     */
    void pushToReserve(const CardModel& card);

    /**
     * @brief 获取当前底牌
     * @return 底牌堆顶部牌的常量引用
     */
    const CardModel& getTopFoundation() const;

    /**
     * @brief 获取视图指针
     * @return StackView 指针
     */
    StackView* getView() const;

    /** 刷新底牌区视图为当前模型状态 */
    void refreshFoundationView();

    /** 刷新备用牌堆视图为当前模型状态 */
    void refreshReserveView();

private:
    /** 备用牌堆中某张牌被点击的处理 */
    void _onReserveClicked(int index);

    /** 堆牌区数据模型 */
    StackModel _model;

    /** 堆牌区视图 */
    StackView* _view;

    /** 翻牌成功回调 */
    FlipCallback _flipCallback;

    /** 回退按钮回调 */
    UndoCallback _undoCallback;
};

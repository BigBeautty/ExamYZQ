#pragma once

#include "cocos2d.h"

class PlayFieldView;
class StackView;

/**
 * @brief 游戏主视图，负责组合和布局 PlayFieldView 与 StackView
 *
 * 按照设计分辨率 1080x2080 布局整个游戏界面：
 * - PlayFieldView 放置在上方（y=kStackHeight，高度 1500）
 * - StackView 放置在下方（y=0，高度 580）
 *
 * GameController 通过 setup 方法将子控制器创建的视图传入，
 * GameView 只负责布局和持有引用，不负责创建子视图。
 */
class GameView : public cocos2d::Node
{
public:
    /** 工厂方法，创建并初始化 GameView 实例 */
    static GameView* create();

    /**
     * @brief 设置子视图并按布局放置
     *
     * 将 PlayFieldView 放在上方，StackView 放在下方。
     * 调用方（GameController）负责创建这两个视图。
     *
     * @param playFieldView 主牌区视图
     * @param stackView 堆牌区视图
     */
    void setup(PlayFieldView* playFieldView, StackView* stackView);

    /** 获取主牌区视图 */
    PlayFieldView* getPlayFieldView() const;

    /** 获取堆牌区视图 */
    StackView* getStackView() const;

private:
    /** 初始化：设置内容大小 */
    bool _init();

    /** 主牌区视图（由外部传入，GameView 不负责创建） */
    PlayFieldView* _playFieldView;

    /** 堆牌区视图（由外部传入，GameView 不负责创建） */
    StackView* _stackView;
};

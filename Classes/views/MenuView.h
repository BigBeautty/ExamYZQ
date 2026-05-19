#pragma once

#include "cocos2d.h"

/**
 * @brief 主菜单视图
 *
 * 用于 AppDelegate 启动后的初始界面，包含菜单背景图与"开始游戏"按钮。
 * 仅承载视图与回调注册；点击按钮触发 _onStartClickCallback。
 */
class MenuView : public cocos2d::Node
{
public:
    /** 开始游戏回调签名：无参 */
    using StartCallback = std::function<void()>;

    /** 工厂方法；构造失败返回 nullptr */
    static MenuView* create();

    /** 注册"开始游戏"按钮回调 */
    void setOnStartClickCallback(const StartCallback& cb) { _onStartClickCallback = cb; }

private:
    /** 私有构造，强制走 create */
    MenuView();
    /** 内部初始化：背景 Sprite（缺失则用纯色 LayerColor）+ 开始按钮 Label */
    bool _init();

    StartCallback _onStartClickCallback;   ///< 开始游戏点击回调
};

#pragma once

#include "cocos2d.h"

/**
 * @brief 菜单场景
 */
class MenuScene : public cocos2d::Scene
{
public:
    // 创建菜单场景，返回autorelease的Scene，会自动调用new+init()
    static cocos2d::Scene* createScene();

    // 菜单场景初始化，填充场景内容、绑定按钮回调等
    bool init() override;

    // 一个便捷的工厂宏，提供MenuScene::create()函数
    CREATE_FUNC(MenuScene);
};

#pragma once

#include <memory>
#include "cocos2d.h"
#include "controllers/GameController.h"

/**
 * @brief 游戏场景
 *
 * 持有 GameController 实例，负责启动游戏对局并将 GameView 挂载到场景树。
 */
class GameScene : public cocos2d::Scene
{
public:
    /** 创建游戏场景，返回 autorelease 的 Scene */
    static cocos2d::Scene* createScene();

    /** 游戏场景初始化 */
    bool init() override;

    CREATE_FUNC(GameScene);

private:
    /** 对局总控制器 */
    std::unique_ptr<GameController> _controller;
};

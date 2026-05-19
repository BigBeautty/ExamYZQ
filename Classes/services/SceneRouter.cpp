#include "services/SceneRouter.h"
#include "scenes/GameScene.h"
#include "scenes/MenuScene.h"

/**
 * 切换到游戏场景：创建 GameScene 并通过 Director 替换当前场景。
 */
void SceneRouter::toGameScene()
{
    auto* scene = GameScene::createScene();
    cocos2d::Director::getInstance()->replaceScene(scene);
}

/**
 * 切换到菜单场景：创建 MenuScene 并通过 Director 替换当前场景。
 */
void SceneRouter::toMenuScene()
{
    auto* scene = MenuScene::createScene();
    cocos2d::Director::getInstance()->replaceScene(scene);
}

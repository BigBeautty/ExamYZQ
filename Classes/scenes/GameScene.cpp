#include "scenes/GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init()) 
    {
        return false;
    }
    _controller = std::make_unique<GameController>();
    if (!_controller->startGame("level")) 
    {
        CCLOG("[GameScene] startGame failed");
        return true;
    }
    if (auto* gv = _controller->getGameView()) 
    {
        addChild(gv);
    }
    return true;
}

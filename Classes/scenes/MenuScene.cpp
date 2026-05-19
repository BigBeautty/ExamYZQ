#include "scenes/MenuScene.h"
#include "services/SceneRouter.h"
#include "views/MenuView.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto* view = MenuView::create();
    if (!view)
    {
        return false;
    }
    view->setOnStartClickCallback(
        []()
        {
            SceneRouter::toGameScene();
        });
    addChild(view, 0);
    return true;
}

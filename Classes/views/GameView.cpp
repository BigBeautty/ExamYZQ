#include "views/GameView.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"
#include "views/LayoutConstants.h"

USING_NS_CC;

GameView* GameView::create()
{
    auto* view = new (std::nothrow) GameView();
    if (view && view->_init())
    {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool GameView::_init()
{
    if (!Node::init())
    {
        return false;
    }

    setContentSize(Size(
        LayoutConstants::kDesignWidth,
        LayoutConstants::kDesignHeight));

    _playFieldView = nullptr;
    _stackView = nullptr;

    return true;
}

void GameView::setup(PlayFieldView* playFieldView, StackView* stackView)
{
    _playFieldView = playFieldView;
    _stackView = stackView;

    if (_stackView)
    {
        _stackView->setPosition(Vec2(0.0f, 0.0f));
        addChild(_stackView, 0);
    }

    if (_playFieldView)
    {
        _playFieldView->setPosition(Vec2(0.0f, LayoutConstants::kStackHeight));
        addChild(_playFieldView, 0);
    }
}

PlayFieldView* GameView::getPlayFieldView() const
{
    return _playFieldView;
}

StackView* GameView::getStackView() const
{
    return _stackView;
}

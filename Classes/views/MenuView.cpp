#include "views/MenuView.h"
#include "views/LayoutConstants.h"

USING_NS_CC;

MenuView::MenuView()
    : _onStartClickCallback(nullptr)
{
}

MenuView* MenuView::create()
{
    auto* view = new (std::nothrow) MenuView();
    if (view && view->_init())
    {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

/**
 * 组装顺序：
 *   1) 设置自身为设计分辨率大小
 *   2) 背景：优先尝试 menu_background.png，加载失败时用纯色 LayerColor 兜底
 *   3) "开始游戏" 按钮：MenuItemLabel 包裹 Label，挂在内置 Menu 上
 */
bool MenuView::_init()
{
    if (!Node::init())
    {
        return false;
    }
    setContentSize(Size(LayoutConstants::kDesignWidth, LayoutConstants::kDesignHeight));
    setAnchorPoint(Vec2::ZERO);

    // 尝试加载背景图片，失败则用纯色兜底
    auto* bg = Sprite::create("menu_background.png");
    if (bg)
    {
        bg->setAnchorPoint(Vec2(0.5f, 0.5f));
        bg->setPosition(Vec2(LayoutConstants::kDesignWidth * 0.5f, LayoutConstants::kDesignHeight * 0.5f));
        const auto bgSize = bg->getContentSize();
        if (bgSize.width > 0 && bgSize.height > 0)
        {
            const float sx = LayoutConstants::kDesignWidth / bgSize.width;
            const float sy = LayoutConstants::kDesignHeight / bgSize.height;
            bg->setScale(std::max(sx, sy));
        }
        addChild(bg, 0);
    }
    else
    {
        auto* fallback = LayerColor::create(
            Color4B(20, 30, 50, 255), LayoutConstants::kDesignWidth, LayoutConstants::kDesignHeight);
        addChild(fallback, 0);
    }

    // 创建"开始游戏"按钮
    auto* label = Label::createWithSystemFont(
        u8"开始游戏", "Arial", 96);
    label->setTextColor(Color4B::BLACK);
    auto* item = MenuItemLabel::create(label,
        [this](Ref* /*sender*/)
        {
            if (_onStartClickCallback)
            {
                _onStartClickCallback();
            }
        });
    item->setAnchorPoint(Vec2(0.5f, 0.5f));
    item->setPosition(Vec2(LayoutConstants::kDesignWidth * 0.5f, LayoutConstants::kDesignHeight * 0.6f));

    auto* menu = Menu::create(item, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 1);
    return true;
}

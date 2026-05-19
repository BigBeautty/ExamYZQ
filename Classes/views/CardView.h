#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
#include <functional>
#include <string>

/**
 * @brief 单张牌的视图
 *
 * 组合底板（card_general.png）+ 花色图（res/suits/）+ 大数字（res/number/big_*.png）
 * + 小数字（res/number/small_*.png）来显示一张完整的扑克牌。
 * 支持点击回调和可点击状态的视觉反馈（不可点击时降低透明度）。
 */
class CardView : public cocos2d::Node
{
public:
    /** 点击回调签名：参数为 cardId */
    using ClickCallback = std::function<void(int cardId)>;

    /**
     * @brief 工厂方法
     * @param model 用于初始化的牌数据
     * @return 创建成功返回 autorelease 的 CardView，失败返回 nullptr
     */
    static CardView* create(const CardModel& model);

    /**
     * @brief 设置点击回调（仅当可点击时触发）
     * @param cb 点击回调函数
     */
    void setClickCallback(const ClickCallback& cb);

    /**
     * @brief 更新可点击状态
     * @param clickable true 时恢复透明度并响应点击，false 时降低透明度并忽略点击
     */
    void setClickable(bool clickable);

    /**
     * @brief 获取关联的 cardId
     * @return 牌的唯一标识
     */
    int getCardId() const;

private:
    CardView();

    /** 内部初始化：组装底板、花色、大数字、小数字 */
    bool _initWithModel(const CardModel& model);

    /** 添加触摸事件监听 */
    void _setupTouchListener();

    /** 根据 CardSuit 获取花色图片相对路径 */
    std::string _getSuitImagePath(int suit) const;

    /** 根据 CardFace 和颜色获取大数字图片相对路径 */
    std::string _getBigNumberImagePath(int face, bool isRed) const;

    /** 根据 CardFace 和颜色获取小数字图片相对路径 */
    std::string _getSmallNumberImagePath(int face, bool isRed) const;

    /** 将 CardFace 数值转换为文件名后缀（0->A, 1->2, ..., 12->K） */
    std::string _faceToString(int face) const;

    int _cardId;                  ///< 关联的牌 ID
    bool _isClickable;            ///< 是否响应点击
    ClickCallback _clickCallback; ///< 点击回调
};

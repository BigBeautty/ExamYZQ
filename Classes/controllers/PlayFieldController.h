#pragma once

#include <functional>
#include <vector>
#include "models/PlayFieldModel.h"
#include "views/PlayFieldView.h"

/**
 * @brief 主牌区控制器
 *
 * 管理主牌区的交互逻辑。
 * 通过回调与 GameController 通信，不直接依赖 GameController。
 */
class PlayFieldController
{
public:
    /**
     * @brief 匹配成功回调
     * @param card 被匹配的牌（数据）
     * @param extractedView 已从 PlayFieldView 分离并 retain 的 CardView 节点
     */
    using MatchCallback = std::function<void(const CardModel& card,
                                              cocos2d::Node* extractedView)>;

    /** 请求匹配回调：参数为被点击的牌 ID */
    using RequestMatchCallback = std::function<void(int cardId)>;

    PlayFieldController();
    ~PlayFieldController();

    /**
     * @brief 初始化主牌区
     * @param cards 主牌区所有牌面数据
     */
    void init(const std::vector<CardModel>& cards);

    /**
     * @brief 设置匹配成功回调
     * @param cb 匹配成功时调用的回调函数
     */
    void setMatchCallback(const MatchCallback& cb);

    /**
     * @brief 设置请求匹配回调
     * @param cb 牌被点击时调用的回调函数
     */
    void setRequestMatchCallback(const RequestMatchCallback& cb);

    /**
     * @brief 尝试匹配指定牌与底牌
     * @param cardId 被点击的牌 ID
     * @param foundationTop 当前底牌
     */
    void tryMatch(int cardId, const CardModel& foundationTop);

    /**
     * @brief 恢复一张牌到主牌区（回退用）
     * @param card 要恢复的牌数据
     */
    void restoreCard(const CardModel& card);

    /**
     * @brief 获取主牌区视图指针
     * @return PlayFieldView 指针
     */
    PlayFieldView* getView() const;

private:
    /** 牌被点击的回调处理 */
    void _onCardClicked(int cardId);

    /** 主牌区数据模型 */
    PlayFieldModel _model;

    /** 主牌区视图 */
    PlayFieldView* _view;

    /** 匹配成功回调 */
    MatchCallback _matchCallback;

    /** 请求匹配回调 */
    RequestMatchCallback _requestMatchCallback;
};

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "cocos2d.h"
#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "views/GameView.h"
#include "views/CardView.h"

/**
 * @brief 游戏对局总控制器
 */

/** 操作类型 */
enum class ActionType
{
    kMatch,  ///< 从主牌区匹配牌到底牌堆
    kFlip    ///< 从备用牌堆翻牌到底牌堆
};

/** 操作记录，用于回退 */
struct ActionRecord
{
    ActionType type;         ///< 操作类型
    CardModel card;          ///< 涉及的牌
    cocos2d::Vec2 origPos;   ///< 原始位置（匹配操作时记录）
    int origId;              ///< 原始ID
};

/**
 * @brief 游戏对局总控制器
 *
 * 协调 PlayFieldController 与 StackController：
 * - 匹配成功时把 PlayFieldView 中提取出的 CardView 挂到 GameView 顶层做飞行动画
 * - 翻牌动画在 StackView 内部完成
 * - 回退时同样产生反向飞行动画
 * - 通过 GameView 管理界面布局，自身不直接操作视图节点的位置
 */
class GameController
{
public:
    GameController();
    ~GameController();

    /**
     * @brief 初始化并开始游戏
     *
     * 加载关卡配置，创建子控制器和 GameView，设置各回调。
     *
     * @param levelId 关卡 ID
     * @return true 初始化成功，false 配置加载失败
     */
    bool startGame(const std::string& levelId);

    /**
     * @brief 获取游戏视图根节点
     *
     * 供 GameScene 挂载到场景树中。
     *
     * @return GameView 指针（autorelease，由 Scene 持有）
     */
    GameView* getGameView() const;

    /**
     * @brief 回退操作
     *
     * 弹出最后一条操作记录并恢复游戏状态。
     */
    void undo();

private:
    /** 主牌区匹配成功回调 */
    void _onCardMatched(const CardModel& card, cocos2d::Node* extractedView);

    /** 备用牌翻牌回调 */
    void _onCardFlipped(const CardModel& card);

    /** 设置各子控制器的回调 */
    void _setupCallbacks();

    /** 主牌区控制器 */
    std::unique_ptr<PlayFieldController> _playFieldCtrl;

    /** 堆牌区控制器 */
    std::unique_ptr<StackController> _stackCtrl;

    /** 游戏主视图（autorelease，由 Scene 持有） */
    GameView* _gameView;

    /** 操作历史栈 */
    std::vector<ActionRecord> _history;
};

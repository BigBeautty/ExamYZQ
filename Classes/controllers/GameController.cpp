#include "controllers/GameController.h"
#include "views/LayoutConstants.h"

USING_NS_CC;

namespace
{
    /** PlayField <-> Foundation 飞行动画时长（秒） */
    constexpr float kCardMoveDuration = 0.35f;
}

GameController::GameController()
    : _playFieldCtrl(nullptr)
    , _stackCtrl(nullptr)
    , _gameView(nullptr)
{
}

GameController::~GameController()
{
}

bool GameController::startGame(const std::string& levelId)
{
    LevelConfig config;
    if (!LevelConfigLoader::load(levelId, config))
    {
        CCLOG("GameController::startGame - Failed to load level: %s", levelId.c_str());
        return false;
    }

    // 创建子控制器并初始化
    _playFieldCtrl = std::make_unique<PlayFieldController>();
    _playFieldCtrl->init(config.playfieldCards);

    _stackCtrl = std::make_unique<StackController>();
    _stackCtrl->init(config.stackCards);

    // 创建 GameView 并通过 setup 传入子视图，由 GameView 负责布局
    _gameView = GameView::create();
    _gameView->setup(_playFieldCtrl->getView(), _stackCtrl->getView());

    // 设置回调
    _setupCallbacks();

    return true;
}

void GameController::_setupCallbacks()
{
    _playFieldCtrl->setRequestMatchCallback(
        [this](int cardId)
        {
            const CardModel& top = _stackCtrl->getTopFoundation();
            _playFieldCtrl->tryMatch(cardId, top);
        });

    _playFieldCtrl->setMatchCallback(
        [this](const CardModel& card, cocos2d::Node* extractedView)
        {
            _onCardMatched(card, extractedView);
        });

    _stackCtrl->setFlipCallback(
        [this](const CardModel& card)
        {
            _onCardFlipped(card);
        });

    _stackCtrl->setUndoCallback(
        [this]()
        {
            undo();
        });
}

/**
 * 匹配成功：被点击的 CardView 已从 PlayFieldView 中分离。
 * 挂到 GameView 顶层做飞行动画，动画结束后压入底牌堆并记录历史。
 */
void GameController::_onCardMatched(const CardModel& card, cocos2d::Node* extractedView)
{
    if (!extractedView)
    {
        _stackCtrl->pushToFoundation(card);
        ActionRecord rec;
        rec.type = ActionType::kMatch;
        rec.card = card;
        rec.origPos = card.position;
        rec.origId = card.id;
        _history.push_back(rec);
        return;
    }

    auto* sv = _stackCtrl->getView();
    auto* pfv = _playFieldCtrl->getView();

    Vec2 startInGame = pfv->getPosition() + card.position;
    Vec2 endInGame = sv->getFoundationWorldPos(_gameView);

    // 挂到 GameView 顶层做飞行动画
    extractedView->setPosition(startInGame);
    _gameView->addChild(extractedView, 100);
    extractedView->release();

    auto* gc = this;
    auto cardCopy = card;
    auto* moveAction = MoveTo::create(kCardMoveDuration, endInGame);
    auto* done = CallFunc::create([gc, cardCopy, extractedView]()
    {
        extractedView->removeFromParent();
        gc->_stackCtrl->pushToFoundation(cardCopy);

        ActionRecord rec;
        rec.type = ActionType::kMatch;
        rec.card = cardCopy;
        rec.origPos = cardCopy.position;
        rec.origId = cardCopy.id;
        gc->_history.push_back(rec);
    });
    extractedView->runAction(Sequence::create(moveAction, done, nullptr));
}

void GameController::_onCardFlipped(const CardModel& card)
{
    ActionRecord rec;
    rec.type = ActionType::kFlip;
    rec.card = card;
    rec.origPos = card.position;
    rec.origId = card.id;
    _history.push_back(rec);
}

void GameController::undo()
{
    if (_history.empty())
    {
        return;
    }

    ActionRecord lastAction = _history.back();
    _history.pop_back();

    if (lastAction.type == ActionType::kMatch)
    {
        CardModel popped = _stackCtrl->popFromFoundation();

        auto* flying = CardView::create(popped);
        if (!flying)
        {
            _playFieldCtrl->restoreCard(popped);
            return;
        }
        flying->setClickable(false);

        auto* sv = _stackCtrl->getView();
        auto* pfv = _playFieldCtrl->getView();

        Vec2 startInGame = sv->getFoundationWorldPos(_gameView);
        Vec2 endInGame = pfv->getPosition() + popped.position;

        flying->setPosition(startInGame);
        _gameView->addChild(flying, 100);

        auto* gc = this;
        auto cardCopy = popped;
        auto* move = MoveTo::create(kCardMoveDuration, endInGame);
        auto* done = CallFunc::create([gc, cardCopy, flying]()
        {
            flying->removeFromParent();
            gc->_playFieldCtrl->restoreCard(cardCopy);
        });
        flying->runAction(Sequence::create(move, done, nullptr));
    }
    else if (lastAction.type == ActionType::kFlip)
    {
        CardModel popped = _stackCtrl->popFromFoundation();

        auto* sv = _stackCtrl->getView();
        auto* gc = this;
        auto cardCopy = popped;
        sv->playUndoFlipAnimation(popped, kCardMoveDuration,
            [gc, cardCopy]()
            {
                gc->_stackCtrl->pushToReserve(cardCopy);
            });
    }
}

GameView* GameController::getGameView() const
{
    return _gameView;
}

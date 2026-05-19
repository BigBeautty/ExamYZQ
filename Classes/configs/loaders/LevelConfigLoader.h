#pragma once

#include <vector>
#include <string>
#include "models/CardModel.h"

/**
 * @brief 关卡配置数据结构
 *
 * 存储从 JSON 配置文件解析出的主牌区和堆牌区牌面数据。
 */
struct LevelConfig
{
    /** 主牌区牌面列表 */
    std::vector<CardModel> playfieldCards;

    /** 堆牌区牌面列表（最后一个元素为初始底牌，其余为备用牌） */
    std::vector<CardModel> stackCards;
};

/**
 * @brief 关卡配置加载器
 *
 * 负责根据关卡 ID 读取对应的 JSON 配置文件，
 * 解析 Playfield 和 Stack 数组为 CardModel 列表。
 * 纯静态方法，不持有任何状态。
 */
class LevelConfigLoader
{
public:
    /**
     * @brief 加载关卡配置
     *
     * 根据 levelId 拼接文件路径，读取并解析 JSON 配置文件，
     * 将 Playfield 和 Stack 数组解析为 CardModel 列表。
     * Playfield 中的牌 id 从 0 开始递增，isClickable 初始为 true。
     * Stack 中的牌 id 从 Playfield 牌数开始递增。
     *
     * @param levelId 关卡 ID，用于拼接配置文件路径
     * @param outConfig 输出的关卡配置数据
     * @return true 加载成功，false 文件不存在或解析失败
     */
    static bool load(const std::string& levelId, LevelConfig& outConfig);

private:
    LevelConfigLoader() = delete;
};



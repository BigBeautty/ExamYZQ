#pragma once

#include <string>

/**
 * @brief 关卡/资源路径辅助
 *
 * 集中管理工程相关路径拼装规则，避免裸字符串散落各处。
 */
class PathUtils
{
public:
    /**
     * @brief 关卡 JSON 文件的相对路径（相对 Resources 目录）
     * @param levelId 关卡 id
     * @return "configs/levels/{levelId}.json"
     */
    static std::string levelConfigPath(const std::string& levelId)
    {
        return std::string("levelConfigs/") + levelId + ".json";
    }

private:
    PathUtils() = delete;
};

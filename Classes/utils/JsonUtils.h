#pragma once

#include <string>
#include "json/document.h"

/**
 * @brief 通用 JSON 读取/序列化辅助函数
 *
 * 封装 cocos2d FileUtils + rapidjson 的常见操作，
 * 解析失败时通过 CCLOG 输出错误并返回 false，调用方自行决定回退行为。
 * 不持有任何状态，纯静态方法。
 */
class JsonUtils
{
public:
    /**
     * 读取 Resources 下的文件并解析为 rapidjson::Document。
     * @param filename 相对 Resources 的文件名，例如 "configs/levels/level.json"
     * @param outDoc 输出文档；解析失败时内容未定义
     * @return true 成功；false 文件不存在/为空/解析失败
     */
    static bool readFileToDocument(const std::string& filename, rapidjson::Document& outDoc);

    /**
     * 将 rapidjson::Value 序列化为字符串（紧凑格式）。
     * @param value 任意 Value
     * @return UTF-8 字符串
     */
    static std::string writeValueToString(const rapidjson::Value& value);

private:
    JsonUtils() = delete;
};

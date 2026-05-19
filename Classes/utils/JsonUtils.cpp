#include "utils/JsonUtils.h"

#include "cocos2d.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

/**
 * 用 cocos2d FileUtils 读取文本，再交给 rapidjson 解析。
 * 任一步失败均通过 CCLOG 输出原因并返回 false，调用方按需做兜底。
 */
bool JsonUtils::readFileToDocument(const std::string& filename, rapidjson::Document& outDoc)
{
    auto* fileUtils = FileUtils::getInstance();
    if (!fileUtils->isFileExist(filename)) {
        CCLOG("[JsonUtils] file not found: %s", filename.c_str());
        return false;
    }

    std::string content = fileUtils->getStringFromFile(filename);
    if (content.empty()) {
        CCLOG("[JsonUtils] file empty: %s", filename.c_str());
        return false;
    }

    outDoc.Parse(content.c_str());
    if (outDoc.HasParseError()) {
        CCLOG("[JsonUtils] parse error in %s, code=%d offset=%zu",
              filename.c_str(),
              static_cast<int>(outDoc.GetParseError()),
              static_cast<size_t>(outDoc.GetErrorOffset()));
        return false;
    }
    return true;
}

std::string JsonUtils::writeValueToString(const rapidjson::Value& value)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    value.Accept(writer);
    return std::string(buffer.GetString(), buffer.GetSize());
}

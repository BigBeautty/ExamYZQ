#include "configs/loaders/LevelConfigLoader.h"

#include "cocos2d.h"
#include "json/document.h"
#include "utils/JsonUtils.h"
#include "utils/PathUtils.h"

USING_NS_CC;

bool LevelConfigLoader::load(const std::string& levelId, LevelConfig& outConfig)
{
    // 拼接关卡配置文件路径
    std::string path = PathUtils::levelConfigPath(levelId);

    // 读取并解析 JSON 文件
    rapidjson::Document doc;
    if (!JsonUtils::readFileToDocument(path, doc))
    {
        CCLOG("[LevelConfigLoader] Failed to load level config: %s", path.c_str());
        return false;
    }

    // 验证文档是对象类型
    if (!doc.IsObject())
    {
        CCLOG("[LevelConfigLoader] Invalid JSON format, root is not an object: %s", path.c_str());
        return false;
    }

    // 清空输出
    outConfig.playfieldCards.clear();
    outConfig.stackCards.clear();

    int currentId = 0;

    // 解析 Playfield 数组
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
    {
        const rapidjson::Value& playfieldArray = doc["Playfield"];
        for (rapidjson::SizeType i = 0; i < playfieldArray.Size(); ++i)
        {
            const rapidjson::Value& cardObj = playfieldArray[i];
            if (!cardObj.IsObject())
            {
                continue;
            }

            CardModel card;
            card.cardFace = cardObj.HasMember("CardFace") ? cardObj["CardFace"].GetInt() : 0;
            card.cardSuit = cardObj.HasMember("CardSuit") ? cardObj["CardSuit"].GetInt() : 0;

            float posX = 0.0f;
            float posY = 0.0f;
            if (cardObj.HasMember("Position") && cardObj["Position"].IsObject())
            {
                const rapidjson::Value& posObj = cardObj["Position"];
                posX = posObj.HasMember("x") ? posObj["x"].GetFloat() : 0.0f;
                posY = posObj.HasMember("y") ? posObj["y"].GetFloat() : 0.0f;
            }
            card.position = Vec2(posX, posY);

            card.id = currentId++;

            outConfig.playfieldCards.push_back(card);
        }
    }

    // 解析 Stack 数组
    if (doc.HasMember("Stack") && doc["Stack"].IsArray())
    {
        const rapidjson::Value& stackArray = doc["Stack"];
        for (rapidjson::SizeType i = 0; i < stackArray.Size(); ++i)
        {
            const rapidjson::Value& cardObj = stackArray[i];
            if (!cardObj.IsObject())
            {
                continue;
            }

            CardModel card;
            card.cardFace = cardObj.HasMember("CardFace") ? cardObj["CardFace"].GetInt() : 0;
            card.cardSuit = cardObj.HasMember("CardSuit") ? cardObj["CardSuit"].GetInt() : 0;

            float posX = 0.0f;
            float posY = 0.0f;
            if (cardObj.HasMember("Position") && cardObj["Position"].IsObject())
            {
                const rapidjson::Value& posObj = cardObj["Position"];
                posX = posObj.HasMember("x") ? posObj["x"].GetFloat() : 0.0f;
                posY = posObj.HasMember("y") ? posObj["y"].GetFloat() : 0.0f;
            }
            card.position = Vec2(posX, posY);

            card.id = currentId++;

            outConfig.stackCards.push_back(card);
        }
    }

    return true;
}

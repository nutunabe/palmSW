#include "JsonParsing.h"

USING_NS_CC;

float JsonParsing::getVolume(char* name) {
    std::ifstream ifs(DATA);
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);

    assert(doc.IsObject());
    assert(doc.HasMember(name));
    assert(doc[name].IsFloat());
    rapidjson::Value& value = doc[name];

    return value.GetFloat();
    //CCLOG("hello = %f", doc["musicVolume"].GetFloat());
    //musicVolume = doc["musicVolume"].GetFloat();
    //soundfxVolume = doc["soundfxVolume"].GetFloat();
}

void JsonParsing::setVolume(char* name, float volume) {
    doc[name].SetFloat(volume);

    std::ofstream ofs(DATA);
    rapidjson::OStreamWrapper osw(ofs);

    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

float JsonParsing::getEnemyDamage(char* name) {
    std::ifstream ifs(DATA);
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("Enemy"));
    assert(doc["Enemy"].IsObject());
    assert(doc["Enemy"][name].IsObject());
    //rapidjson::Value& value = doc["Enemy"];
    //assert(value[name].IsArray());
    assert(doc["Enemy"][name].HasMember("damage"));
    assert(doc["Enemy"][name]["damage"].IsFloat());
    //assert(value.HasMember("damage"));

    return doc["Enemy"][name]["damage"].GetFloat();
}

float JsonParsing::getEnemyVelocity(char* name) {
    std::ifstream ifs(DATA);
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("Enemy"));
    assert(doc["Enemy"].IsObject());
    assert(doc["Enemy"][name].IsObject());
    //rapidjson::Value& value = doc["Enemy"];
    //assert(value[name].IsArray());
    assert(doc["Enemy"][name].HasMember("velocity"));
    assert(doc["Enemy"][name]["velocity"].IsFloat());
    //assert(value.HasMember("damage"));
    //assert(value.IsInt());
    return doc["Enemy"][name]["velocity"].GetFloat();
}

float JsonParsing::getPlayerDamage() {
    std::ifstream ifs(DATA);
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("Player"));
    assert(doc["Player"].IsObject());
    assert(doc["Player"].HasMember("damage"));
    assert(doc["Player"]["damage"].IsFloat());
    return doc["Player"]["damage"].GetFloat();
}

float JsonParsing::getPlayerVelocity() {
    std::ifstream ifs(DATA);
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("Player"));
    assert(doc["Player"].IsObject());
    assert(doc["Player"].HasMember("velocity"));
    assert(doc["Player"]["velocity"].IsFloat());
    return doc["Player"]["velocity"].GetFloat();
}

int JsonParsing::getPlayerHealth() {
    std::ifstream ifs(DATA);
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("Player"));
    assert(doc["Player"].IsObject());
    assert(doc["Player"].HasMember("health"));
    assert(doc["Player"]["health"].IsInt());
    return doc["Player"]["health"].GetInt();
}

int JsonParsing::getPlayerStamina() {
    std::ifstream ifs(DATA);
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("Player"));
    assert(doc["Player"].IsObject());
    assert(doc["Player"].HasMember("stamina"));
    assert(doc["Player"]["stamina"].IsInt());
    return doc["Player"]["stamina"].GetInt();
}
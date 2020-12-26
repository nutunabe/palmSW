#pragma once
#ifndef __JSON_PARSING_H__

#include <cocos2d.h>
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <include/rapidjson/ostreamwrapper.h>
#include <include/rapidjson/filereadstream.h>
#include "include/rapidjson/writer.h"
#include "include/rapidjson/prettywriter.h"
#include <fstream>
#include "Definitions.h"


class JsonParsing
{
private:
	rapidjson::Document doc;

public:
	float getVolume(char* name);
	void setVolume(char* name, float volume);

	float getEnemyDamage(char *name);
	float getEnemyVelocity(char *name);

	float getPlayerDamage();
	float getPlayerVelocity();
	int getPlayerHealth();
	int getPlayerStamina();

	int getLevel();
};

#endif // !__JSON_PARSING_H__
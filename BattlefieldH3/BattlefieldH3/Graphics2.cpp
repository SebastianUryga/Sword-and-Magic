#include "Graphics2.h"

Graphics2& graphics2 = Graphics2::Get();

Graphics2::Graphics2()
{
}

Graphics2::~Graphics2()
{
}

void Graphics2::init()
{
	creaturesTextures[Monster::MonsterType::ORK1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK1].Load("ORK_01");
	creaturesTextures[Monster::MonsterType::ORK2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK2].Load("ORK_02");
	creaturesTextures[Monster::MonsterType::ORK3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK3].Load("ORK_03");

	
	
}

Graphics2& Graphics2::Get()
{
	static Graphics2 gr;
	return gr;
}

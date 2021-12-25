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
	creaturesTextures[Monster::MonsterType::NO_CREATURE] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::NO_CREATURE].portrait = std::make_shared<sf::Texture>();
	creaturesTextures[Monster::MonsterType::NO_CREATURE].portrait->loadFromFile("Textures/No_Creature_portrait.png");
	creaturesTextures[Monster::MonsterType::ORK1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK1].Load("ORK_01");
	creaturesTextures[Monster::MonsterType::ORK2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK2].Load("ORK_02");
	creaturesTextures[Monster::MonsterType::ORK3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK3].Load("ORK_03");

	creaturesTextures[Monster::MonsterType::TROLL1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::TROLL1].Load("Troll_01_1");
	creaturesTextures[Monster::MonsterType::TROLL2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::TROLL2].Load("Troll_02_1");
	creaturesTextures[Monster::MonsterType::TROLL3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::TROLL3].Load("Troll_03_1");

	creaturesTextures[Monster::MonsterType::KNIGHT1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::KNIGHT1].Load("Knight_01");
	creaturesTextures[Monster::MonsterType::KNIGHT2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::KNIGHT2].Load("Knight_02");
	creaturesTextures[Monster::MonsterType::KNIGHT3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::KNIGHT3].Load("Knight_03");
	
	creaturesTextures[Monster::MonsterType::ELF1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ELF1].Load("Elf_01_");
	creaturesTextures[Monster::MonsterType::ELF2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ELF2].Load("Elf_02_");
	creaturesTextures[Monster::MonsterType::ELF3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ELF3].Load("Elf_03_");

	backgroundsTextures[Background::BACKGROUND1] = std::make_shared<sf::Texture>();
	backgroundsTextures[Background::BACKGROUND1]->loadFromFile("Textures/game_background_1/game_background_1.png");
	/*backgroundsTextures[Background::BACKGROUND2] = std::make_shared<sf::Texture>();
	backgroundsTextures[Background::BACKGROUND2]->loadFromFile("Textures/game_background_2/game_background_2.png");
	backgroundsTextures[Background::BACKGROUND3] = std::make_shared<sf::Texture>();
	backgroundsTextures[Background::BACKGROUND3]->loadFromFile("Textures/game_background_3/game_background_3.png");
	*/
	
}

Graphics2& Graphics2::Get()
{
	static Graphics2 gr;
	return gr;
}

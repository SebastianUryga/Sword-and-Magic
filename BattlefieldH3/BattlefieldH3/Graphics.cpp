#include "GuiHandler.h"

Graphics& graphics = Graphics::Get();

Graphics::Graphics()
{
	this->menuBackgroud = std::make_shared<sf::Texture>();
	this->battleBackgrouds = std::make_shared<sf::Texture>();
	this->allCreaturePortraits = std::make_shared<sf::Texture>();
	this->battleBackgrouds->setRepeated(true);
	this->battleObsticles[BattleObstacle::Type::ROCK1] = std::make_shared<sf::Texture>();
	this->battleObsticles[BattleObstacle::Type::ROCK2] = std::make_shared<sf::Texture>();
	this->battleObsticles[BattleObstacle::Type::ROCK3] = std::make_shared<sf::Texture>();
	this->battleObsticles[BattleObstacle::Type::ROCK4] = std::make_shared<sf::Texture>();
	this->battleObsticles[BattleObstacle::Type::SCIELETON1] = std::make_shared<sf::Texture>();
	this->creaturePortraits[Monster::NO_CREATURE] = sf::IntRect(386, 627, 58, 64);
	this->creaturePortraits[Monster::PIKEMAN] = sf::IntRect(8, 6, 58, 64);
	this->creaturePortraits[Monster::HALBERDIER] = sf::IntRect(70, 6, 58, 64);
	this->creaturePortraits[Monster::ARCHER] = sf::IntRect(134, 6, 58, 64);
	this->creaturePortraits[Monster::MARKSMEN] = sf::IntRect(194, 6, 58, 64);
	this->creaturePortraits[Monster::GRIFFIN] = sf::IntRect(256, 6, 58, 64);
	this->creaturePortraits[Monster::ROYAL_GRIFFIN] = sf::IntRect(320, 6, 58, 64);
	this->creaturePortraits[Monster::SWORDSMAN] = sf::IntRect(386, 6, 58, 64);
	this->creaturePortraits[Monster::CRUSADER] = sf::IntRect(456, 6, 58, 64);
}


Graphics::~Graphics()
{

}

void Graphics::Init()
{
	this->menuBackgroud->loadFromFile("Textures\\background.jpg");
	this->battleBackgrouds->loadFromFile("Textures\\CmBkDrMt.png");

	this->battleUnitsSheets[Monster::PIKEMAN] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::HALBERDIER] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::MARKSMEN] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::ARCHER] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::GRIFFIN] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::ROYAL_GRIFFIN] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::SWORDSMAN] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::CRUSADER] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::MONK] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::ZEALOT] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::CAVALIER] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::ANGEL] = std::make_shared<sf::Texture>();
	this->battleUnitsSheets[Monster::PIKEMAN]->loadFromFile("Textures\\Pikeman.png");
	this->battleUnitsSheets[Monster::HALBERDIER]->loadFromFile("Textures\\Halberdier.png");
	this->battleUnitsSheets[Monster::ARCHER]->loadFromFile("Textures\\Archer.png");
	this->battleUnitsSheets[Monster::MARKSMEN]->loadFromFile("Textures\\Marksman.png");
	this->battleUnitsSheets[Monster::GRIFFIN]->loadFromFile("Textures\\Griffin.png");
	this->battleUnitsSheets[Monster::ROYAL_GRIFFIN]->loadFromFile("Textures\\Royal Griffin.png");
	this->battleUnitsSheets[Monster::SWORDSMAN]->loadFromFile("Textures\\Swordsman.png");
	this->battleUnitsSheets[Monster::CRUSADER]->loadFromFile("Textures\\Crusader.png");
	this->battleUnitsSheets[Monster::MONK]->loadFromFile("Textures\\Monk.png");
	this->battleUnitsSheets[Monster::ZEALOT]->loadFromFile("Textures\\Zealot.png");
	this->battleUnitsSheets[Monster::CAVALIER]->loadFromFile("Textures\\Cavalier.png");
	this->battleUnitsSheets[Monster::ANGEL]->loadFromFile("Textures\\Angel.png");
	this->allCreaturePortraits->loadFromFile("Textures\\Creatures Portraits.png");
	this->battleObsticles[BattleObstacle::Type::ROCK1]->loadFromFile("Textures\\ObDRk01.png");
	this->battleObsticles[BattleObstacle::Type::ROCK2]->loadFromFile("Textures\\ObDRk02.png");
	this->battleObsticles[BattleObstacle::Type::ROCK3]->loadFromFile("Textures\\ObDRk03.png");
	this->battleObsticles[BattleObstacle::Type::ROCK4]->loadFromFile("Textures\\ObDRk04.png");
	this->battleObsticles[BattleObstacle::Type::SCIELETON1]->loadFromFile("Textures\\ObDino3.png");
}

Graphics& Graphics::Get()
{
	static Graphics gr;
	return gr;
}


sf::IntRect Graphics::selectPortrait(Monster type)
{
	return Graphics::Get().creaturePortraits[type];
}


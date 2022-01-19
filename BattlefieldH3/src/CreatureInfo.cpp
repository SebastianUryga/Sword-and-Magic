#include "GuiHandler.h"
#include "CreatureInfo.h"

CreatureInfo::CreatureInfo(float x, float y, Monster type)
	:WindowObject(x, y, 500,350,GH.globalFont )
{
	this->background.setFillColor(sf::Color(150, 150, 150, 255));
	portrait.setPosition(x, y+ 20);
	portrait.setTexture(*graphics2.creaturesTextures[type].idle[0]);
	portrait.setScale(0.5, 0.5);
	const auto& stat = creaturesStats[type];
	this->addText(creatureToString[type],sf::Vector2f(300,10));
	this->addText("Attack:\t\t\t  " + std::to_string(stat.attack),sf::Vector2f(250, 40));
	this->addText("Defence:\t\t\t " + std::to_string(stat.defence),sf::Vector2f(250, 70));
	this->addText("Damage:\t\t\t " + std::to_string(stat.damage),sf::Vector2f(250, 100));
	this->addText("Attack Speed:\t " + std::to_string(stat.attackSpeed).substr(0,4),sf::Vector2f(250, 130));
	this->addText("Arrows:\t\t\t " + std::to_string(stat.arrows),sf::Vector2f(250, 160));
	this->addText("Max Hp:\t\t\t " + std::to_string(stat.hp),sf::Vector2f(250, 190));
	this->addText("Move Speed:\t\t " + std::to_string(stat.speed).substr(0, 4),sf::Vector2f(250, 220));
}

CreatureInfo::CreatureInfo(float x, float y, BattleUnit* unit)
	:CreatureInfo(x,y,unit->getType())
{
}

CreatureInfo::~CreatureInfo()
{
}

void CreatureInfo::render(sf::RenderTarget* target)
{
	WindowObject::render(target);
	target->draw(portrait);
}

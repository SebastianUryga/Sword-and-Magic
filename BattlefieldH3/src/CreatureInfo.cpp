#include "CreatureInfo.h"
#include "Graphics2.h"
#include "BattleUnit.h"

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
	:WindowObject(x, y, 500, 370, GH.globalFont)
{
	if (x + 500 > Config.windowSize.x) x -= ((x + 500)- Config.windowSize.x);
	if (y + 370 > Config.windowSize.y) y -= ((y + 370) - Config.windowSize.y);
	this->setPos(x, y);
	this->background.setFillColor(sf::Color(150, 150, 150, 255));
	portrait.setPosition(x, y + 20);
	portrait.setTexture(*graphics2.creaturesTextures[unit->getType()].idle[0]);
	portrait.setScale(0.5, 0.5);
	const auto& stat = creaturesStats[unit->getType()];
	this->addText(creatureToString[unit->getType()], sf::Vector2f(300, 10));
	this->addText("Attack:\t\t\t  " + std::to_string(stat.attack) + 
		"("+ std::to_string(unit->attack<0 ? 0 : unit->attack) + ")",
		sf::Vector2f(250, 40));
	this->addText("Defence:\t\t\t " + std::to_string(stat.defence) + 
		"(" + std::to_string(unit->defence < 0 ? 0 : unit->defence) +")",
		sf::Vector2f(250, 70));
	this->addText("Damage:\t\t\t " + std::to_string(stat.damage) +
		"(" + std::to_string(unit->damage < 0 ? 0 : unit->damage) +")",
		sf::Vector2f(250, 100));
	this->addText("Attack Speed:\t " + std::to_string(stat.attackSpeed).substr(0, 4)
		,sf::Vector2f(250, 130));
	this->addText("Arrows:\t\t\t " + std::to_string(stat.arrows) +
		"(" + std::to_string(unit->arrows < 0 ? 0 : unit->arrows) + ")",
		sf::Vector2f(250, 160));
	this->addText("Max Hp:\t\t\t " + std::to_string(stat.hp), sf::Vector2f(250, 190));
	this->addText("Actual Hp:\t\t " + std::to_string(unit->hp), sf::Vector2f(250, 220));
	this->addText("Move Speed:\t\t " + std::to_string(stat.speed).substr(0, 4) +
		"(" + std::to_string(unit->speed < 0 ? 0 : unit->speed).substr(0, 4) + ")"
		, sf::Vector2f(250, 250));

	auto pos = sf::Vector2f(x + 10.f,y + 290.f);
	for (auto spell : unit->castedSpellList)
	{
		if (castedSpellIcons.size() > 3) break;
		this->castedSpellIcons.push_back(sf::Sprite());
		this->castedSpellIcons.back().setTexture(*graphics2.allSpellIcons);
		this->castedSpellIcons.back().setTextureRect(Graphics2::selectSpellIcon(spell.type));
		this->castedSpellIcons.back().setPosition(pos);
		pos.x += 75;
	}
}

CreatureInfo::~CreatureInfo()
{
}

void CreatureInfo::render(sf::RenderTarget* target)
{
	WindowObject::render(target);
	target->draw(portrait);
	for(auto& i : castedSpellIcons)
		target->draw(i);
}

#include "pch.h"
#include "Battlefield.h"
#include "GuiHandler.h"

void Battlefield::initButtons()
{
	this->buttons["Quit"] = std::make_shared<Button>(
		1330, 730, 60, 30, &this->font, "Quit"
		);
	this->buttons["Quit"]->addFuctionallity([=]() {close(); });
	this->interactiveElem.push_back(this->buttons["Quit"]);
}

void Battlefield::sortUnits()
{
	// do naprawy
	std::sort(units.begin(), units.end(),
		[](std::shared_ptr<BattleUnit> a, std::shared_ptr<BattleUnit> b)
	{
		return a->getPos().y < b->getPos().y ||
			(a->getPos().y == b->getPos().y);
	});
}

bool Battlefield::containsIsBattlefield(sf::Vector2i pos)
{
	if(pos.x < 0 || pos.y < 0 
		|| pos.x >= BATTLEFIELDWIDHT || pos.y >= BATTLEFIELDHEIGHT)
		return false;
	return true;
}

void Battlefield::changeUnitPos(BattleUnit* unit, sf::Vector2i oldPos, sf::Vector2i newPos)
{
	if (oldPos == newPos)
		return;
	if (unit != tiles[oldPos.x][oldPos.y].unit)
		std::cout << "cos nie gra 1" << std::endl;
	if (tiles[newPos.x][newPos.y].unit ||
		tiles[newPos.x][newPos.y].blocked)
		std::cout << "cos nie gra 2" << std::endl;

	if (tiles[oldPos.x][oldPos.y].unit == unit)
	{
		tiles[oldPos.x][oldPos.y].unit = nullptr;
		tiles[oldPos.x][oldPos.y].blocked = false;
	}
	tiles[newPos.x][newPos.y].unit = unit;
	tiles[newPos.x][newPos.y].blocked = true;
	unit->setPos(newPos);
	//this->sortUnits();
}

void Battlefield::addUnit(std::shared_ptr<BattleUnit> unit, sf::Vector2i pos, bool enemy)
{
	//if(unit->isBig())
	if (!this->containsIsBattlefield(pos))
	{
		std::cout << "erorr: wrong position" << std::endl; return;
	}
	this->tiles[pos.x][pos.y].unit = unit.get();
	this->tiles[pos.x][pos.y].blocked = true;
	this->units.push_back(unit);
	unit->setPos(pos);
	unit->setEnemy(enemy);
	
}

void Battlefield::close()
{
	WindowObject::close();
	BH.battlefield = nullptr;
}

Battlefield::Battlefield()
	:WindowObject(20,20,1500,800,GH.globalFont)
{
	this->initButtons();

	this->tiles.resize(BATTLEFIELDWIDHT);
	for (auto& tile : this->tiles)
		tile.resize(BATTLEFIELDHEIGHT);

	for (int x = 0; x < tiles.size() ; x++)
	for (int y = 0; y < tiles[x].size(); y++)
	{
		tiles[x][y].pos = sf::Vector2i(x, y);
		tiles[x][y].shape = sf::RectangleShape(sf::Vector2f(BTILEWIDTH,BTILEHEIGHT));
		tiles[x][y].shape.setPosition(50 + (x * BTILEWIDTH), 150 + (y * BTILEHEIGHT));
		tiles[x][y].shape.setFillColor(sf::Color(20, 20, 20, 90));
		tiles[x][y].shape.setOutlineThickness(1);
		tiles[x][y].shape.setOutlineColor(sf::Color::Yellow);
		tiles[x][y].blocked = false;
		tiles[x][y].unit = nullptr;
	}
	this->backgroud.setTexture(*graphics.battleBackgrouds);
	this->backgroud.setPosition(30, 30);
	this->backgroud.setScale(1.5, 1.5);
	this->backgroud.setTextureRect(sf::IntRect(0, 0, 900, 500));
	this->addUnit(std::make_shared<BattleUnit>(Monster::ANGEL), sf::Vector2i(1, 10), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::CRUSADER), sf::Vector2i(2, 0), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::CRUSADER), sf::Vector2i(19, 0), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::CRUSADER), sf::Vector2i(21, 5), true);
	/*this->addUnit(std::make_shared<BattleUnit>(Monster::CRUSADER), sf::Vector2i(3, 3));
	this->addUnit(std::make_shared<BattleUnit>(Monster::SWORDSMAN), sf::Vector2i(23, 7));
	this->addUnit(std::make_shared<BattleUnit>(Monster::SWORDSMAN), sf::Vector2i(6, 6));
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(22, 10));
	this->addUnit(std::make_shared<BattleUnit>(Monster::MARKSMEN), sf::Vector2i(1, 12));
	this->addUnit(std::make_shared<BattleUnit>(Monster::MARKSMEN), sf::Vector2i(24, 6));
	this->addUnit(std::make_shared<BattleUnit>(Monster::MARKSMEN), sf::Vector2i(3, 10));
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(23, 4));
	*/this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(2, 6), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(22, 2), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::MARKSMEN), sf::Vector2i(4, 1), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(22, 0),true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(1, 5),true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::MARKSMEN), sf::Vector2i(21, 12), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(22, 8), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::SWORDSMAN), sf::Vector2i(23, 12), true);

}

Battlefield::~Battlefield()
{
}

void Battlefield::update(const float dt, const sf::Vector2i mousePos)
{
	WindowObject::update(dt, mousePos);
	BH.update(dt);
}

void Battlefield::render(sf::RenderTarget* target)
{
	WindowObject::render(target);
	target->draw(this->backgroud);
	for(auto v : this->tiles)
		for (auto tile : v)
		{
			if (tile.unit)
				tile.shape.setFillColor(sf::Color(120, 120, 120, 120));
			else
				tile.shape.setFillColor(sf::Color(20, 20, 20, 90));
			target->draw(tile.shape);
		}
	for (auto& unit : this->units)
		unit->render(target);
	for (auto& btn : this->buttons)
		btn.second->render(target);

}

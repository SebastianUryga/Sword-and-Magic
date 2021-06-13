#include "GuiHandler.h"
#include "Battlefiled.h"

void Battlefield::initButtons()
{
	this->buttons["Quit"] = std::make_shared<Button>(
		1400, 730, 60, 30, &this->font, "Quit"
		);
	this->buttons["Quit"]->addFuctionallity([=]() {close(); });
	this->interactiveElem.push_back(this->buttons["Quit"]);
	if (this->mode == GameMode::Game)
	{
		this->buttons["Defensive"] = std::make_shared<Button>(
			100, 770, 170, 30, &this->font, "Defensive Position"
			);
		this->buttons["Defensive"]->addFuctionallity([=]() {
			for (auto& unit : selectedUnits)
			{
				if (unit->getAlive())
					unit->giveOrder(Order::DEFENSIVE_POS);
			}
		});
		this->interactiveElem.push_back(this->buttons["Defensive"]);

		this->buttons["Agresive"] = std::make_shared<Button>(
			310, 770, 170, 30, &this->font, "Agresive Position"
			);
		this->buttons["Agresive"]->addFuctionallity([=]() {
			for (auto& unit : selectedUnits)
			{
				if (unit->getAlive())
					unit->giveOrder(Order::AGRESIVE_POSITION);
			}
		});
		this->interactiveElem.push_back(this->buttons["Agresive"]);
	}
	if (this->mode == GameMode::Editor)
	{
		this->buttons["Save"] = std::make_shared<Button>(
			1400, 300, 60, 30, &this->font, "Save"
			);
		this->buttons["Save"]->addFuctionallity([=]() {save("startMap.txt"); });
		this->interactiveElem.push_back(this->buttons["Save"]);

		this->buttons["Load"] = std::make_shared<Button>(
			1400, 360, 60, 30, &this->font, "Load"
			);
		this->buttons["Load"]->addFuctionallity([=]() {load("startMap.txt"); });
		this->interactiveElem.push_back(this->buttons["Load"]);

		this->gar1 = std::make_shared<Garrnison>(
			army[0], this->background.getPosition() + sf::Vector2f(50, 740));
		this->gar2 = std::make_shared<Garrnison>(
			army[1], this->background.getPosition() + sf::Vector2f(850, 740));
		for (auto slot : gar1->slots)
		{
			this->texts.push_back(slot->number);
			this->interactiveElem.push_back(slot);
		}
		for (auto slot : gar2->slots)
		{
			this->texts.push_back(slot->number);
			this->interactiveElem.push_back(slot);
		}

	}
}

void Battlefield::initStartUnits()
{	
	this->addObsticle(BattleObstacle::Type::ROCK2, sf::Vector2i(10, 9));
	this->addObsticle(BattleObstacle::Type::ROCK3, sf::Vector2i(18, 1));
	this->addObsticle(BattleObstacle::Type::ROCK1, sf::Vector2i(8, 5));
	this->addObsticle(BattleObstacle::Type::ROCK1, sf::Vector2i(3, 1));
	this->addObsticle(BattleObstacle::Type::ROCK2, sf::Vector2i(3, 2));
	this->addObsticle(BattleObstacle::Type::ROCK3, sf::Vector2i(1, 3));
	this->addObsticle(BattleObstacle::Type::ROCK4, sf::Vector2i(16, 8));
	/*this->addUnit(std::make_shared<BattleUnit>(Monster::ANGEL), sf::Vector2i(1, 10), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::CAVALIER), sf::Vector2i(2, 0), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::CRUSADER), sf::Vector2i(19, 0), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::CRUSADER), sf::Vector2i(3, 4), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::SWORDSMAN), sf::Vector2i(1, 7), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(22, 2), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::GRIFFIN), sf::Vector2i(21, 11), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::GRIFFIN), sf::Vector2i(1, 5),true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::MARKSMEN), sf::Vector2i(21, 9), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(22, 8), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(0, 8), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(1, 1), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::CAVALIER), sf::Vector2i(23, 6), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::CAVALIER), sf::Vector2i(22, 10), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::HALBERDIER), sf::Vector2i(6, 7), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::HALBERDIER), sf::Vector2i(6, 9), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::HALBERDIER), sf::Vector2i(7, 9), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::PIKEMAN), sf::Vector2i(0, 9), false);
	*/
	this->addUnit(std::make_shared<BattleUnit>(Monster::CAVALIER), sf::Vector2i(22, 10), true);

	this->addUnit(std::make_shared<BattleUnit>(Monster::HALBERDIER), sf::Vector2i(6, 7), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::HALBERDIER), sf::Vector2i(6, 9), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::HALBERDIER), sf::Vector2i(7, 9), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::HALBERDIER), sf::Vector2i(7, 10), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::HALBERDIER), sf::Vector2i(5, 9), true);

	this->addUnit(std::make_shared<BattleUnit>(Monster::ZEALOT), sf::Vector2i(21, 3), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ZEALOT), sf::Vector2i(14, 3), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ZEALOT), sf::Vector2i(1, 2), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ZEALOT), sf::Vector2i(17, 3), true);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ZEALOT), sf::Vector2i(12, 8), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::ZEALOT), sf::Vector2i(1, 4), false);
	this->addUnit(std::make_shared<BattleUnit>(Monster::SWORDSMAN), sf::Vector2i(2, 4), false);

	this->addUnit(std::make_shared<BattleUnit>(Monster::ARCHER), sf::Vector2i(20, 1), true);

}

void Battlefield::sortUnits()
{
	std::sort(units.begin(), units.end(),
		[](const std::shared_ptr<BattleUnit>& a, const std::shared_ptr<BattleUnit>& b)
	{
		return a->getPos().y < b->getPos().y ||
			(a->getPos().y == b->getPos().y && a->getPos().x < b->getPos().x);
	});
}

void Battlefield::initArmy()
{
	this->army[0] = { {Monster::PIKEMAN, 5},{Monster::SWORDSMAN, 4},{Monster::ARCHER, 2},
		{Monster::ARCHER, 4} ,{Monster::PIKEMAN, 2}, {Monster::ZEALOT, 3} ,{Monster::NO_CREATURE, 0} };
	this->army[1] = { {Monster::PIKEMAN, 15},{Monster::GRIFFIN, 5},{Monster::ARCHER, 5},
		{Monster::MARKSMEN, 7} ,{Monster::ROYAL_GRIFFIN, 3}, {Monster::NO_CREATURE, 0} ,{Monster::NO_CREATURE, 0} };

}

bool Battlefield::containsIsBattlefield(sf::Vector2i pos) const
{
	if (pos.x < 0 || pos.y < 0
		|| pos.x >= BATTLEFIELD_WIDHT || pos.y >= BATTLEFIELD_HEIGHT)
		return false;
	return true;
}

std::shared_ptr<BattleUnit> Battlefield::getUnit(sf::Vector2i pos) const
{
	for (auto unit : this->units)
		if (pos == unit->getPos())
			return unit;
	return nullptr;
}

sf::Vector2i Battlefield::getSize() const
{
	if (tiles.size() > 0)
		return sf::Vector2i(tiles.size(), tiles[0].size());
	return sf::Vector2i(0, 0);
}

BattleTile& Battlefield::getTile(sf::Vector2i pos)
{
	if (this->containsIsBattlefield(pos))
		return tiles[pos.x][pos.y];
	std::cout << "error: position doesn't contain in Battlefield" << std::endl;
	assert(0);
	return tiles[0][0];
}

BattleTile& Battlefield::getTile(int x, int y)
{
	auto pos = sf::Vector2i(x, y);
	return this->getTile(pos);
}

const BattleTile& Battlefield::getTile(const sf::Vector2i pos) const
{
	if (this->containsIsBattlefield(pos))
		return tiles[pos.x][pos.y];
	else
	{
		std::cout << "cos nie gra w GetTile" << std::endl;
		return tiles[0][0];
	}	
}

bool Battlefield::isTileBlocked(const sf::Vector2i pos) const
{
	if(!containsIsBattlefield(pos))
		return true;
	return getTile(pos).blocked;
}

void Battlefield::changeUnitPos(BattleUnit* unit, sf::Vector2i oldPos, sf::Vector2i newPos)
{
	if (oldPos == newPos)
		return;
	if (unit != this->getTile(oldPos).unit)
		std::cout << "cos nie gra 1" << std::endl;
	if (this->getTile(newPos).unit &&
		this->isTileBlocked(newPos) &&
		unit->getPos2() != newPos)
		std::cout << "cos nie gra 2" << std::endl;

	if (this->getTile(oldPos).unit == unit)
	{
		this->getTile(oldPos).unit = nullptr;
		this->getTile(oldPos).blocked = false;
		this->getTile(unit->getPos2()).unit = nullptr;
		this->getTile(unit->getPos2()).blocked = false;
	}
	this->getTile(newPos).unit = unit;
	this->getTile(newPos).blocked = true;
	unit->setPos(newPos);
	this->getTile(unit->getPos2()).unit = unit;
	this->getTile(unit->getPos2()).blocked = true;
	this->sortUnits();
}

void Battlefield::addUnit(std::shared_ptr<BattleUnit> unit, sf::Vector2i pos, bool enemy)
{
	//if(unit->isBig())
	if (!this->containsIsBattlefield(pos) ||
		this->isTileBlocked(pos))
	{
		std::cout << "erorr: wrong position" << std::endl; return;
	}

	this->units.push_back(unit);
	unit->setPathfinder(this);
	unit->setPos(pos);
	unit->setEnemy(enemy);
	this->tiles[unit->getPos().x][unit->getPos().y].unit = unit.get();
	this->tiles[unit->getPos2().x][unit->getPos2().y].unit = unit.get();
	this->tiles[unit->getPos().x][unit->getPos().y].blocked = true;
	this->tiles[unit->getPos2().x][unit->getPos2().y].blocked = true;
}

void Battlefield::addObsticle(BattleObstacle::Type type, sf::Vector2i pos)
{
	if (!this->containsIsBattlefield(pos)) return;

	std::shared_ptr<BattleObstacle> obj = std::make_shared<BattleObstacle>();
	obj->sprite.setTexture(*graphics.battleObsticles[type]);
	
	obj->sprite.setPosition(sf::Vector2f(50 + pos.x * B_TILE_WIDTH, 150 + pos.y * B_TILE_HEIGHT));
	obj->usedTiles = battleObstacleParametrs[type].usedTiles;
	obj->sprite.setOrigin(B_TILE_WIDTH * sf::Vector2f(obj->usedTiles[0].size() -1, obj->usedTiles.size() - 1));
	obj->pos = pos;
	for (int y = 0; y < obj->usedTiles.size(); y++)
		for (int x = 0; x < obj->usedTiles[y].size(); x++)
		{
			int xVal = obj->pos.x - x;
			int yVal = obj->pos.y - y;
			if(this->containsIsBattlefield(sf::Vector2i(xVal,yVal)))
			{
				BattleTile& tile = this->getTile(xVal, yVal);
				if (obj->usedTiles[y][x])
				{
					tile.blocked = true;
				}
			}
		}
	this->obstacles.push_back(obj);
}

void Battlefield::removeUnit(std::shared_ptr<BattleUnit> unit)
{
	for (int i = 0; i < this->units.size(); i++)
		if (unit == this->units[i])
			this->units.erase(this->units.begin() + i);
	this->tiles[unit->getPos().x][unit->getPos().y].blocked = false;
	this->tiles[unit->getPos().x][unit->getPos().y].unit = nullptr;
	this->tiles[unit->getPos2().x][unit->getPos2().y].blocked = false;
	this->tiles[unit->getPos2().x][unit->getPos2().y].unit = nullptr;
}

void Battlefield::removeObsticle(std::shared_ptr<BattleObstacle> obs)
{
	for (int i = 0; i < this->obstacles.size(); i++)
		if (obs == this->obstacles[i])
			this->obstacles.erase(this->obstacles.begin() + i);
}

void Battlefield::close()
{
	WindowObject::close();
	BH.battlefield = nullptr;
}

void Battlefield::clickLeft(bool down, bool previousState)
{
	if (down)
	{
		if (this->mode == GameMode::Editor)
		{
			auto pos = sf::Mouse::getPosition() / (int)B_TILE_WIDTH - sf::Vector2i{ 1,3 };
			if (!this->containsIsBattlefield(pos)) return;
			BattleTile& clickedTile = this->getTile(pos );
			if(!clickedTile.blocked && !clickedTile.unit)
				this->addObsticle(BattleObstacle::Type::SCIELETON1, clickedTile.pos);
		}
		if (this->mode == GameMode::Game)
		{
			this->selectingArea.setSize(sf::Vector2f(0,0));
			this->selectingArea.setFillColor(sf::Color(120, 120, 120, 120));
			this->selectingArea.setPosition(
				sf::Mouse::getPosition().x,
				sf::Mouse::getPosition().y);
		}
	}
	if (previousState && down == false)
	{
		if (this->mode == GameMode::Game)
		{
			this->selectingArea.setFillColor(sf::Color(120, 120, 120, 0));
			this->selectedUnits.clear();
			sf::FloatRect bounds = this->selectingArea.getGlobalBounds();
			for (int x = (bounds.left - 50) / B_TILE_WIDTH; x < (bounds.left + bounds.width - 50) / B_TILE_WIDTH; x++)
				for (int y = (bounds.top - 150) / B_TILE_WIDTH; y < (bounds.top + bounds.height - 150) / B_TILE_HEIGHT; y++)
				{
					if (!this->containsIsBattlefield(sf::Vector2i(x, y)))
						continue;
				
					this->tiles[x][y].shape.setFillColor(sf::Color(190, 20, 20, 250));
					if (this->tiles[x][y].unit && this->tiles[x][y].unit->getAlive())
						if (this->selectedUnits.find(this->tiles[x][y].unit) == this->selectedUnits.end())
							this->selectedUnits.insert(this->tiles[x][y].unit);
				}
		}
	}
}

void Battlefield::clickRight(bool down, bool previousState)
{
	if (previousState && down == false)
	{
		auto pos = sf::Mouse::getPosition() / (int)B_TILE_WIDTH - sf::Vector2i{ 1,3 };
		if (!this->containsIsBattlefield(pos)) return;
		BattleTile& clickedTile = this->getTile(pos);
		for (auto u : this->selectedUnits)
		{
			if (clickedTile.unit && clickedTile.blocked)
			{
				if (u->choseTarget(clickedTile.unit))
					u->giveOrder(Order::ATTACK);
			}
			else
			{
				if (u->giveDestenation(clickedTile.pos))
					u->giveOrder(Order::MOVE);
			}

		}
	}
}

void Battlefield::hover(bool on)
{
	if (on)
	{
		if (this->mode == GameMode::Game)
		{
			this->selectingArea.setSize(
				-1.f * (selectingArea.getPosition() - (sf::Vector2f)sf::Mouse::getPosition()));

		}
	}

}
Battlefield::Battlefield(GameMode mode)
	:WindowObject(20, 20, 1500, 800, GH.globalFont), InterfaceElem()
{
	this->shape = sf::FloatRect(20, 20,
		1400,
		750);
	
	this->mode = mode;
	this->selectingArea.setFillColor(sf::Color(120, 120, 120, 120));
	
	this->initArmy();
	this->initButtons();

	this->tiles.resize(BATTLEFIELD_WIDHT);
	for (auto& tile : this->tiles)
		tile.resize(BATTLEFIELD_HEIGHT);

	for (int x = 0; x < tiles.size(); x++)
		for (int y = 0; y < tiles[x].size(); y++)
		{
			tiles[x][y].pos = sf::Vector2i(x, y);
			tiles[x][y].shape = sf::RectangleShape(sf::Vector2f(B_TILE_WIDTH, B_TILE_HEIGHT));
			tiles[x][y].shape.setPosition(50 + (x * B_TILE_WIDTH), 150 + (y * B_TILE_HEIGHT));
			tiles[x][y].shape.setFillColor(sf::Color(20, 20, 20, 90));
			tiles[x][y].shape.setOutlineColor(sf::Color::Yellow);
			tiles[x][y].blocked = false;
			tiles[x][y].unit = nullptr;
		}
	this->backgroud.setTexture(*graphics.battleBackgrouds);
	this->backgroud.setPosition(30, 30);
	this->backgroud.setScale(1.5, 1.5);
	this->backgroud.setTextureRect(sf::IntRect(0, 0, 900, 500));

}

Battlefield::~Battlefield()
{
}

void Battlefield::update(const float dt)
{
	WindowObject::update(dt);
	if(this->mode == GameMode::Game)
		BH.update(dt);
	if (this->mode == GameMode::Editor)
	{
		for (auto& unit : this->units)
			unit->updateAnimation(dt);
	}
}

void Battlefield::render(sf::RenderTarget* target)
{
	WindowObject::render(target);
	target->draw(this->backgroud);
	for (auto v : this->tiles)
		for (auto tile : v)
		{
			if (tile.unit)
			{
				tile.shape.setFillColor(sf::Color(120, 120, 120, 70));
				if(this->selectedUnits.find(tile.unit) != this->selectedUnits.end())
					tile.shape.setFillColor(sf::Color(190, 190, 190, 200));
			}
			else if(tile.blocked)
				tile.shape.setFillColor(sf::Color(200, 120, 200, 20));
			else
				tile.shape.setFillColor(sf::Color(20, 20, 20, 20));
			target->draw(tile.shape);
		}
	for (auto& obj : this->obstacles)
		target->draw(obj->sprite);
	for (auto& unit : this->units)
		unit->render(target);
	for (auto& btn : this->buttons)
		btn.second->render(target);
	target->draw(selectingArea);
	if (this->mode == GameMode::Editor)
	{
		gar1->render(target);
		gar2->render(target);
	}
}

void Battlefield::save(const std::string& path)
{
	std::fstream file;
	file.open(path);
	file.clear();
	file << this->obstacles.size() << std::endl;
	for (auto obs : this->obstacles)
	{
		file << (int)obs->type << " ";
		file << obs->pos.x << " " << obs->pos.y << std::endl;
	}
	file << units.size() << std::endl;
	for (auto u : this->units)
	{
		file << u->getType().monster << std::endl;
		file << u->getPos().x << " " << u->getPos().y << " ";
		file << u->getPos2().x <<" "<< u->getPos2().y << " ";
		file << u->getAlive() <<" " <<u->isEnemy()<< std::endl;
	}
	for(int i = 0 ; i < 2 ; i++)
	for (auto troop : this->army[i])
	{
		file << " " << troop.monster.monster << " " << troop.count << " ";
	}
	
}

bool Battlefield::load(const std::string& path)
{
	std::fstream file;
	file.open(path);
	int temp,type;
	sf::Vector2i pos1, pos2;
	// loading Obstacles
	file >> temp;
	if (temp < 0) return false;
	for (int i = 0; i < temp; i++)
	{
		file >> type;
		file >> pos1.x >> pos1.y;
		this->addObsticle(BattleObstacle::Type(type), pos1);
	}
	// loading Units
	bool enemy, alive;
	file >> temp;
	if (temp < 0) return false;
	this->units.resize(temp);
	for (int i = 0; i < temp; i++)
	{
		file >> type;
		file >> pos1.x >> pos1.y >> pos2.x >> pos2.y;
		file >> alive >> enemy;
		this->addUnit(std::make_shared<BattleUnit>(Monster(type)),pos1,enemy);
	}
	// loading Armys
	for (int i = 0; i < 2; i++)
	for (auto& troop : this->army[i])
	{
		int type;
		file >> type >> troop.count;
		Monster temp(type);
		troop.monster = temp;
	}

	return true;
}

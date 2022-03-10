#include "Battlefiled.h"
#include "BattleHandler.h"

void Battlefield::initButtons()
{
	auto pos = sf::Vector2f((140.f / 160.f) * Config.windowSize.x, (77.f / 90.f) * Config.windowSize.y);
	this->buttons["Quit"] = std::make_shared<Button>(
		pos.x, pos.y, 60, 50, &this->font, "Quit");
	this->buttons["Quit"]->addFuctionallity([=]() { close(); });
	this->interactiveElem.push_back(this->buttons["Quit"]);
	if (this->mode == GameMode::Game)
	{
		pos = sf::Vector2f((9.f / 160.f) * Config.windowSize.x, (77.f / 90.f) * Config.windowSize.y);
		this->buttons["Defensive"] = std::make_shared<Button>(
			pos.x, pos.y, 190, 50, &this->font, "Defensive Position");
		this->buttons["Defensive"]->addFuctionallity([=]() {
			for (auto& unit : selectedUnits)
			{
				if (unit->getAlive())
					unit->giveOrder(Order::DEFENSIVE_POS);
			}
		});
		this->interactiveElem.push_back(this->buttons["Defensive"]);

		pos = sf::Vector2f((29.f / 160.f) * Config.windowSize.x, (77.f / 90.f) * Config.windowSize.y);
		this->buttons["Agresive"] = std::make_shared<Button>(
			pos.x, pos.y, 190, 50, &this->font, "Agresive Position");
		this->buttons["Agresive"]->addFuctionallity([=]() {
			for (auto& unit : selectedUnits)
			{
				if (unit->getAlive())
					unit->giveOrder(Order::AGRESIVE_STANCE);
			}
		});
		this->interactiveElem.push_back(this->buttons["Agresive"]);
		
		pos = sf::Vector2f((59.f / 160.f) * Config.windowSize.x, (75.f / 90.f) * Config.windowSize.y);
		this->activeSpellIcon.setPosition(pos);
		this->activeSpellIcon.setTexture(*graphics2.allSpellIcons);

		pos = sf::Vector2f((67.f / 160.f) * Config.windowSize.x, (77.f / 90.f) * Config.windowSize.y);
		this->buttons["SpellBook"] = std::make_shared<Button>(
			pos.x, pos.y, 170, 50, &this->font, "Spell Book");
		this->buttons["SpellBook"]->addFuctionallity([=]() {
			assert(!players[0]->isAI());
			GH.pushWindowT<SpellBook>(this->spellToCast,*players[0]);
		});
		this->interactiveElem.push_back(this->buttons["SpellBook"]);

		this->cooldownNumber = std::make_shared<sf::Text>(
			std::to_string(std::ceil(players[0]->getSpellCooldown())),
			GH.globalFont, 30);

		pos = sf::Vector2f((84.f / 160.f) * Config.windowSize.x, (78.f / 90.f) * Config.windowSize.y);
		this->cooldownNumber->setPosition(pos);
		this->texts.push_back(cooldownNumber);

		pos = sf::Vector2f((90.f / 160.f) * Config.windowSize.x, (77.f / 90.f) * Config.windowSize.y);
		this->buttons["PauseStartGame"] = std::make_shared<Button>(
			pos.x, pos.y, 170, 50, &this->font, "Pause Game");
		this->buttons["PauseStartGame"]->addFuctionallity([=]() {
			if (gamePaused)
			{
				buttons["PauseStartGame"]->setText("Pause Game");
				gamePaused = false;
			}
			else
			{
				buttons["PauseStartGame"]->setText("Resume Game");
				gamePaused = true;
			}
		});
		this->interactiveElem.push_back(this->buttons["PauseStartGame"]);
	}
	if (this->mode == GameMode::Editor)
	{
		pos = sf::Vector2f((75.f / 160.f) * Config.windowSize.x, (78.f / 90.f) * Config.windowSize.y);
		this->buttons["Save"] = std::make_shared<Button>(
			pos.x, pos.y, 60, 40, &this->font, "Save");
		this->buttons["Save"]->addFuctionallity([=]() { save("res/startMap.txt"); });
		this->interactiveElem.push_back(this->buttons["Save"]);

		pos = sf::Vector2f((65.f / 160.f) * Config.windowSize.x, (78.f / 90.f) * Config.windowSize.y);
		this->buttons["Load"] = std::make_shared<Button>(
			pos.x, pos.y, 60, 40, &this->font, "Load");
		this->buttons["Load"]->addFuctionallity([=]() { 
			load("res/startMap.txt");
			this->gar1->updateSlots();
			this->gar2->updateSlots();
		});
		this->interactiveElem.push_back(this->buttons["Load"]);

		pos = sf::Vector2f((63.f / 160.f) * Config.windowSize.x, (74.f / 90.f) * Config.windowSize.y);
		this->buttons["Background"] = std::make_shared<Button>(
			pos.x, pos.y, 200, 35, &this->font, "Change Background");
		this->buttons["Background"]->addFuctionallity([=]() {
			if(backgroundType == Background::BACKGROUND1)
				this->backgroundType = Background::BACKGROUND2;
			else if(backgroundType == Background::BACKGROUND2)
				this->backgroundType = Background::BACKGROUND3;
			else if (backgroundType == Background::BACKGROUND3)
				this->backgroundType = Background::BACKGROUND4;
			else
				this->backgroundType = Background::BACKGROUND1;

			backgroud.setTexture(*graphics2.backgroundsTextures[backgroundType]);
		});
		this->interactiveElem.push_back(this->buttons["Background"]);

		pos = sf::Vector2f((5.f / 160.f) * Config.windowSize.x, (74.f / 90.f) * Config.windowSize.y);
		this->gar1 = std::make_shared<Garrnison>(
			players[0]->army, this->background.getPosition() + sf::Vector2f(pos.x, pos.y));
		pos = sf::Vector2f((85.f / 160.f) * Config.windowSize.x, (74.f / 90.f) * Config.windowSize.y);
		this->gar2 = std::make_shared<Garrnison>(
			players[1]->army, this->background.getPosition() + sf::Vector2f(pos.x, pos.y));
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

void Battlefield::initTileMap()
{
	this->tiles.resize(Config.battlefiledTileWidth);
	for (auto& tile : this->tiles)
		tile.resize(Config.battlefiledTileHegiht);

	for (int x = 0; x < (int)tiles.size(); x++)
		for (int y = 0; y < (int)tiles[x].size(); y++)
		{
			tiles[x][y].pos = sf::Vector2i(x, y);
			tiles[x][y].shape = sf::RectangleShape(sf::Vector2f(Config.tileWidth, Config.tileHeight));
			tiles[x][y].shape.setPosition(sf::Vector2f(
				x * Config.tileWidth,
				y * Config.tileHeight) + Config.battlefieldOffset);
			tiles[x][y].shape.setFillColor(sf::Color(20, 20, 20, 90));
			tiles[x][y].shape.setOutlineColor(sf::Color::Yellow);
			//tiles[x][y].shape.setOutlineThickness(0.5f);
			tiles[x][y].blocked = false;
			tiles[x][y].unit = nullptr;
		}
}

void Battlefield::initMovmentMarker()
{
	this->movmentMarker.setOutlineColor(sf::Color::Green);
	this->movmentMarker.setOutlineThickness(1);
	this->movmentMarker.setFillColor(sf::Color::Transparent);
	this->movmentMarker.setOrigin(sf::Vector2f(-Config.tileWidth/2,-Config.tileHeight / 2));
	this->movmentMarker.setRadius(0);
	
}

void Battlefield::sortUnits()
{
	std::sort(units.begin(), units.end(), [](const std::shared_ptr<BattleUnit>& a, const std::shared_ptr<BattleUnit>& b) {
		return a->getPos().y < b->getPos().y || 
			(a->getPos().y == b->getPos().y && a->getAlive() < b->getAlive()) ||
			(a->getPos().y == b->getPos().y && a->getAlive() == b->getAlive() && a->getPos().x > b->getPos().x);
	});
}

void Battlefield::initArmy()
{
	this->army[0] = { { Monster::PIKEMAN, 5 }, { Monster::SWORDSMAN, 4 }, { Monster::ARCHER, 2 }, { Monster::ARCHER, 4 }, { Monster::PIKEMAN, 2 }, { Monster::ZEALOT, 3 }, { Monster::NO_CREATURE, 0 } };
	this->army[1] = { { Monster::PIKEMAN, 15 }, { Monster::GRIFFIN, 5 }, { Monster::ARCHER, 5 }, { Monster::MARKSMEN, 7 }, { Monster::ROYAL_GRIFFIN, 3 }, { Monster::NO_CREATURE, 0 }, { Monster::NO_CREATURE, 0 } };
}

void Battlefield::initPlayers()
{
	this->players.resize(2);
	this->players[0] = std::make_shared<Player>(false, 20);
	if (Config.PvP)
		this->players[1] = std::make_shared<Player>(false, 10);
	else
		this->players[1] = std::make_shared<Player>(true, 10);
}

void Battlefield::initPlayersArmy2()
{
	this->players[0]->army = { { Monster::ELF1, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 2 }, { Monster::NO_CREATURE, 3 }, { Monster::NO_CREATURE, 0 } };
	this->players[1]->army = { { Monster::KNIGHT2, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 1 }, { Monster::NO_CREATURE, 3 }, { Monster::NO_CREATURE, 0 }, { Monster::NO_CREATURE, 0 } };
}

void Battlefield::putMovmentMarker(const sf::Vector2i& tilePos, bool attck)
{
	if (attck)
		this->movmentMarker.setOutlineColor(sf::Color::Red);
	else
		this->movmentMarker.setOutlineColor(sf::Color::Green);
	auto pixelPos = sf::Vector2f(
		tilePos.x * Config.tileWidth,
		tilePos.y * Config.tileHeight) + Config.battlefieldOffset;
	this->movmentMarker.setPosition(pixelPos);
	this->movmentMarker.setRadius(0);
	this->markerVisableTimeLeft = 0.5f;
}

void Battlefield::setBackground(Background background)
{
	this->backgroundType = background;
	switch (background)
	{
	case Background::BACKGROUND1:
	{
		int start = Config.battlefiledTileWidth / 8;
		int end = (Config.battlefiledTileWidth / 7) * 3;
		for (int i = start; i < end; i++)
			tiles[i][0].blocked = true;
		break;
	}
	case Background::BACKGROUND2:
	{
		for (int i = 0; i < Config.battlefiledTileWidth; i++)
			tiles[i][0].blocked = true;
		int start = (Config.battlefiledTileWidth / 6);
		int end = (Config.battlefiledTileWidth / 4);
		for (int i = start; i < end; i++)
			tiles[i][1].blocked = true;
		break;
		for (int i = 0; i < Config.battlefiledTileWidth; i++)
			tiles[i][Config.battlefiledTileHegiht - 2].blocked = true;
	}
	case Background::BACKGROUND3:
		for (int i = 0; i < Config.battlefiledTileWidth; i++)
			tiles[i][0].blocked = true;
		for (int i = 0; i < Config.battlefiledTileWidth; i++)
			tiles[i][Config.battlefiledTileHegiht - 2].blocked = true;
		break;
	case Background::BACKGROUND4:
		for (int i = 0; i < Config.battlefiledTileWidth; i++)
			tiles[i][0].blocked = true;
		for (int i = 0; i < Config.battlefiledTileWidth; i++)
			tiles[i][Config.battlefiledTileHegiht - 2].blocked = true;
		break;
	default:
		break;
	}
	for (int i = 0; i < Config.battlefiledTileWidth; i++)
		tiles[i][Config.battlefiledTileHegiht - 1].blocked = true;
}

bool Battlefield::containsIsBattlefield(sf::Vector2i pos) const
{
	if (pos.x < 0 || pos.y < 0
		|| pos.x >= Config.battlefiledTileWidth || pos.y >= Config.battlefiledTileHegiht)
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
		return sf::Vector2i((int)tiles.size(), (int)tiles[0].size());
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

bool Battlefield::areUnitSelected() const
{
	return !selectedUnits.empty();
}

bool Battlefield::isTileBlocked(const sf::Vector2i pos) const
{
	if (!containsIsBattlefield(pos))
		return true;
	return getTile(pos).blocked;
}

void Battlefield::changeUnitPos(BattleUnit* unit, sf::Vector2i oldPos, sf::Vector2i newPos)
{
	if (oldPos == newPos)
		return;
	
	for (auto tile : unit->getUsedTilesPos())
	{
		this->getTile(tile).unit = nullptr;
		this->getTile(tile).blocked = false;
	}
	unit->setPos(newPos);
	for (auto tile : unit->getUsedTilesPos())
	{
		this->getTile(tile).unit = unit;
		this->getTile(tile).blocked = true;
	}
	this->sortUnits();
}

bool Battlefield::addUnit(std::shared_ptr<BattleUnit> unit, sf::Vector2i pos, bool enemy)
{
	//if(unit->isBig())
	unit->setPos(pos);
	for (auto tile : unit->getUsedTilesPos())
	if (!this->containsIsBattlefield(tile) || this->isTileBlocked(tile))
	{
		return false;
	}

	unit->setPathfinder(this);
	
	unit->setEnemy(enemy);
	if (this->players[unit->isEnemy()]->isAI() == false)
		unit->giveOrder(Order::DEFENSIVE_POS);

	for (auto tile : unit->getUsedTilesPos())
	{
		this->getTile(tile).unit = unit.get();
		this->getTile(tile).blocked = true;
	}
	unit->onDoubleClick = [=]()
	{
		if (this->players[unit->isEnemy()]->isAI() == false)
		{
			selectedUnits.clear();
			for (auto u : units)
			{
				if (u->getAlive()
					&& u->isEnemy() == unit->isEnemy()
					&& u->getType() == unit->getType())
					selectedUnits.insert(u.get());
			}
		}
		
	};
	unit->onClick = [=]()
	{
		if (!unit->getAlive()) return;
		if (this->spellToCast != Spell::SpellType::NONE)
		{
			
			Spell::castSpellOnUnit(*unit, this->spellToCast);
			BH.spellCasted(this->spellToCast, this->players[0].get());
			this->spellToCast = Spell::SpellType::NONE;
			
		}
		else
		{
			selectedUnits.clear();
			if(this->players[unit->isEnemy()]->isAI() == false)
				selectedUnits.insert(unit.get());
		}
	};
	
	this->interactiveElem.push_back(unit);
	this->units.push_back(unit);
	this->sortUnits();
	return true;
}

void Battlefield::addObsticle(BattleObstacle::Type type, sf::Vector2i tilePos)
{
	if (!this->containsIsBattlefield(tilePos))
		return;
	auto pixelPos = sf::Vector2f(
		tilePos.x * Config.tileWidth,
		tilePos.y * Config.tileHeight) + Config.battlefieldOffset;
	std::shared_ptr<BattleObstacle> obj = std::make_shared<BattleObstacle>();
	obj->sprite.setTexture(*graphics2.battleObsticles[type]);
	obj->type = type;
	obj->sprite.setPosition(pixelPos);
	auto scalar = (2 * Config.tileWidth) / 260.f;
	obj->sprite.setScale(scalar, scalar);
	obj->usedTiles = battleObstacleParametrs[type].usedTiles;
	obj->sprite.setOrigin(sf::Vector2f(
		Config.tileWidth * obj->usedTiles[0].size() - 1,
		Config.tileHeight * obj->usedTiles.size() - 1));

	obj->sprite.setOrigin(sf::Vector2f(graphics2.battleObsticles[type]->getSize()));
	obj->sprite.move(sf::Vector2f(2*Config.tileWidth, Config.tileHeight));
	obj->pos = tilePos;
	for (int y = 0; y < (int)obj->usedTiles.size(); y++)
		for (int x = 0; x < (int)obj->usedTiles[y].size(); x++)
		{
			int xVal = obj->pos.x - x;
			int yVal = obj->pos.y - y;
			if (this->containsIsBattlefield(sf::Vector2i(xVal, yVal)))
			{
				BattleTile& tile = this->getTile(xVal, yVal);
				if (obj->usedTiles[y][x])
				{
					tile.blocked = true;
					tile.obstacles.push_back(obj);
				}
			}
		}
	this->obstacles.push_back(obj);
	std::sort(this->obstacles.begin(),this->obstacles.end(), [](const std::shared_ptr<BattleObstacle>& a, const std::shared_ptr<BattleObstacle>& b) {
		return a->pos.y < b->pos.y ||
			(a->pos.y == b->pos.y && a->pos.x > b->pos.x);
	});
}

void Battlefield::removeUnit(std::shared_ptr<BattleUnit> unit)
{
	unit->thread = false;
	for (int i = 0; i < (int)this->units.size(); i++)
		if (unit == this->units[i])
			this->units.erase(this->units.begin() + i);
	for (auto pos : unit->getUsedTilesPos())
	{
		this->getTile(pos).blocked = false;
		this->getTile(pos).unit = nullptr;
	}
}

void Battlefield::removeObsticle(std::shared_ptr<BattleObstacle> obs)
{
	for (int i = 0; i < (int)this->obstacles.size(); i++)
		if (obs == this->obstacles[i])
		{
			this->obstacles.erase(this->obstacles.begin() + i);
		}
}

void Battlefield::close()
{
	WindowObject::close();
		
	BH.battlefield = nullptr;
}

void Battlefield::keyPressed([[maybe_unused]] const sf::Keyboard& key)
{

}

void Battlefield::activate()
{
	WindowObject::activate();
	if (this->mode == GameMode::Editor)
	{
		gar1->updateSlots();
		gar2->updateSlots();
	}
}

void Battlefield::clickLeft(bool down, bool previousState)
{
	if (down)
	{
		/*if (this->mode == GameMode::Editor)
		{
			auto tilePos = GH.mouseTilePos;
			if (!this->containsIsBattlefield(tilePos))
				return;
			BattleTile& clickedTile = this->getTile(tilePos);
			if (!clickedTile.blocked && !clickedTile.unit)
				this->addObsticle(BattleObstacle::Type::ROCK1, clickedTile.pos);
		}*/
		if (this->mode == GameMode::Game)
		{
			this->selectingArea.setSize(sf::Vector2f(0, 0));
			this->selectingArea.setFillColor(sf::Color(120, 120, 120, 120));
			this->selectingArea.setPosition(GH.mousePosWindow);
		}
	}
	if (previousState && down == false)
	{
		if (this->mode == GameMode::Game)
		{
			this->selectingArea.setFillColor(sf::Color(120, 120, 120, 0));
			if (this->spellToCast != Spell::SpellType::NONE)
			{
				auto tilePos = GH.mouseTilePos;
				if (!this->containsIsBattlefield(tilePos))
					return;
				BattleTile& clickedTile = this->getTile(tilePos);
				if (clickedTile.unit && clickedTile.unit->getAlive())
				{
					Spell::castSpellOnUnit(*clickedTile.unit, this->spellToCast);
					BH.spellCasted(this->spellToCast, this->players[0].get());
					this->spellToCast = Spell::SpellType::NONE;
				}
			}
			bool clearSelected = true;
			for(auto btn : this->buttons) 
				if(btn.second->contains(GH.mousePosWindow))
					clearSelected = false;
			if(clearSelected) this->selectedUnits.clear();

			sf::FloatRect bounds = this->selectingArea.getGlobalBounds();
			for (int x = (bounds.left - Config.battlefieldOffset.x) / Config.tileWidth;
			x < (bounds.left + bounds.width - Config.battlefieldOffset.x) / Config.tileWidth;
			x++)
				for (int y = (bounds.top - Config.battlefieldOffset.y) / Config.tileHeight;
				y < (bounds.top + (bounds.height - Config.battlefieldOffset.y)) / Config.tileHeight;
				y++)
				{
					if (!this->containsIsBattlefield(sf::Vector2i(x, y)))
						continue;

					this->tiles[x][y].shape.setFillColor(sf::Color(190, 20, 20, 250));
					auto unit = this->tiles[x][y].unit;
					if (unit && unit->getAlive())
						if (this->players[unit->isEnemy()]->isAI() == false)
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
		this->spellToCast = Spell::SpellType::NONE;

		auto tilePos = GH.mouseTilePos;
		if (!this->containsIsBattlefield(tilePos))
			return;
		BattleTile& clickedTile = this->getTile(tilePos);

		if (this->mode == GameMode::Editor)
		{
			if (!clickedTile.obstacles.empty())
			{
				this->removeObsticle(clickedTile.obstacles.front());
				clickedTile.obstacles.erase(clickedTile.obstacles.begin());
			}
		}

		for (auto u : this->selectedUnits)
		{
			int i = 0;
			int p = (int)std::floor(sqrt(this->selectedUnits.size()));
			auto temp = clickedTile.pos + sf::Vector2i { i % p, i / p };
			if (clickedTile.unit && clickedTile.blocked)
			{
				if (u->choseTarget(clickedTile.unit))
				{
					u->giveOrder(Order::ATTACK);
					this->putMovmentMarker(temp, true);
				}
			}
			else
			{
				if (u->giveDestenation(temp))
				{
					u->giveOrder(Order::MOVE);
					this->putMovmentMarker(temp, false);
				}
			}
			i++;
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
				-1.f * (selectingArea.getPosition() - GH.mousePosWindow));
		}
	}
	else
	{
		this->selectingArea.setFillColor(sf::Color(120, 120, 120, 0));
	}
}

Battlefield::Battlefield(GameMode mode) :
	WindowObject(20.f, 20.f, Config.windowSize.x -20.f, Config.windowSize.y -20.f, GH.globalFont),
	InterfaceElem()
{
	this->shape = sf::FloatRect(-20.f, -20.f, Config.windowSize.x + 20.f, Config.windowSize.y + 20.f);

	this->mode = mode;
	this->backgroundType = Background::BACKGROUND1;

	this->selectingArea.setFillColor(sf::Color(120, 120, 120, 0));
	
	//this->initArmy();
	this->initPlayers();
	this->initButtons();
	this->initMovmentMarker();
	this->initTileMap();
	
	//this->backgroud.setTexture(*graphics.battleBackgrouds);
	this->backgroud.setTexture(*graphics2.backgroundsTextures[Background::BACKGROUND1]);
	this->backgroud.setPosition(
		Config.battlefieldOffset - sf::Vector2f(10, 320));
	auto size = graphics2.backgroundsTextures[Background::BACKGROUND1]->getSize();
	auto toScaleX = (float)Config.windowSize.x / size.x;
	auto toScaleY = (float)Config.windowSize.y / size.y;
	this->backgroud.setScale(toScaleX, toScaleY);
	//this->backgroud.setTextureRect(sf::IntRect(0, 0, 900, 500));

	this->spellToCast = Spell::SpellType::NONE;
}

Battlefield::~Battlefield()
{
}

void Battlefield::updateMovmentMarker(const float dt)
{
	if (this->markerVisableTimeLeft > 0.f)
	{
		this->markerVisableTimeLeft -= dt;
		this->movmentMarker.setRadius(this->movmentMarker.getRadius() + (40 * dt));
		this->movmentMarker.move(sf::Vector2f(-dt * 40, -dt * 40));
	}
	else
		this->movmentMarker.setRadius(0);
}

void Battlefield::update(const float dt)
{
	WindowObject::update(dt);
	
	if (this->mode == GameMode::Game)
	{
		for (auto& player : this->players)
			if (gamePaused)
				player->update(0.f);
			else
				player->update(dt);

		bool cooldownPassed = this->players[0]->getSpellCooldown() <= 0;
		this->buttons["SpellBook"]->block(!cooldownPassed);
		this->cooldownNumber->setString(std::to_string((int)std::ceil(players[0]->getSpellCooldown())));
		this->activeSpellIcon.setTextureRect(Graphics2::selectSpellIcon(this->spellToCast));

		bool makeGreenBtn = false, makeRedBtn = false;
		if (!this->selectedUnits.empty())
		{
			for (auto u : this->selectedUnits)
			{
				auto order = u->getOrder();
				if (order == Order::MOVE || order == Order::DEFENSIVE_POS)
					makeGreenBtn = true;
				if (order == Order::ATTACK || order == Order::AGRESIVE_STANCE)
					makeRedBtn = true;
			}
		}
		this->buttons["Agresive"]->changeColorRed(makeRedBtn);
		this->buttons["Defensive"]->changeColorGreen(makeGreenBtn);
		this->updateMovmentMarker(dt);
		BH.update(dt);
	}
	if (this->mode == GameMode::Editor)
	{
		for (auto& unit : this->units)
			unit->updateAnimation(dt);
	}
}

void Battlefield::render(sf::RenderTarget* target)
{
	//sf::Clock measureTime;

	WindowObject::render(target);
	target->draw(this->backgroud);
	
	for (auto u : this->units)
	{
		if (this->selectedUnits.find(u.get()) != this->selectedUnits.end())
		{
			if (u->getTarget())
				for (auto tile : u->getTarget()->getUsedTilesPos())
				{
					this->getTile(tile).shape.setFillColor(sf::Color(240, 5, 5, 100));
					target->draw(this->getTile(tile).shape);
				}
			for (auto tile : u->getUsedTilesPos())
			{
				this->getTile(tile).shape.setFillColor(sf::Color(190, 190, 190, 200));
				target->draw(this->getTile(tile).shape);
			}
		}
	}
	//for (auto v : this->tiles)
	//	for (auto tile : v)
	//		if (tile.blocked)
	//			target->draw(tile.shape);
	//std::cout << "tiles render: " << measureTime.restart().asMilliseconds() << std::endl;
	if(this->units.empty())
	for (auto& obj : this->obstacles)
		target->draw(obj->sprite);
	int i = 0;
	for (auto& unit : this->units)
	{
		while (this->obstacles.size() > i && this->obstacles[i]->pos.y <= unit->getPos().y)
		{
			target->draw(this->obstacles[i]->sprite);
			i++;
		}
		unit->render(target);
	}
	while (this->obstacles.size() > i)
	{
		target->draw(this->obstacles[i]->sprite);
		i++;
	}
	//std::cout << "units render: " << measureTime.restart().asMilliseconds() << std::endl;

	if (this->markerVisableTimeLeft > 0.f) 
		target->draw(this->movmentMarker);
	for (auto& btn : this->buttons)
		btn.second->render(target);
	target->draw(activeSpellIcon);
	//std::cout << "buttons render: " << measureTime.restart().asMilliseconds() << std::endl;

	if(this->cooldownNumber)
		target->draw(*this->cooldownNumber);
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
	auto saveMapSize = true;
	file << saveMapSize << std::endl;
	if (saveMapSize)
	{
		Config.save(file);
	}
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
		file << u->getPos2().x << " " << u->getPos2().y << " ";
		file << u->getAlive() << " " << u->isEnemy() << std::endl;
	}
	for (int i = 0; i < 2; i++)
		for (auto troop : this->players[i]->army)
		{
			file << " " << troop.monster.monster << " " << troop.count << " ";
		}
	file << std::endl;
	for (int i = 0; i < 2; i++)
	{
		file << players[i]->getActuallMana() << " ";
		file << players[i]->availbleSpells.size() << std::endl;
		for (auto spell : players[i]->availbleSpells)
		{
			file << " " << (int)spell.spell << " ";
		}
	}
	file << std::endl;
	file << (int) this->backgroundType << std::endl;
}

bool Battlefield::load(const std::string& path)
{
	std::fstream file;
	file.open(path);
	int temp, type;
	sf::Vector2i pos1, pos2;
	//check if custom game
	file >> temp;
	if (temp == true)
	{
		if (mode == GameMode::Game)
		{
			Config.load(file, false);
		}
		else if(mode == GameMode::Editor)
		{
			Config.load(file, true);
		}
		this->initTileMap();
		this->players[1]->setAI(!Config.PvP);
	}
	// loading Obstacles
	file >> temp;
	if (temp < 0)
		return false;
	for (int i = 0; i < temp; i++)
	{
		file >> type;
		file >> pos1.x >> pos1.y;
		this->addObsticle(BattleObstacle::Type(type), pos1);
	}
	// loading Units
	bool enemy, alive;
	file >> temp;
	if (temp < 0)
		return false;
	this->units.reserve(temp);
	for (int i = 0; i < temp; i++)
	{
		file >> type;
		file >> pos1.x >> pos1.y >> pos2.x >> pos2.y;
		file >> alive >> enemy;
		this->addUnit(std::make_shared<BattleUnit>(Monster(type)), pos1, enemy);
	}
	// loading Armys
	for (int i = 0; i < 2; i++)
		for (auto& troop : this->players[i]->army)
		{
			int type;
			file >> type >> troop.count;
			Monster temp(type);
			troop.monster = temp;
		}
	// loading Spells
	for (int i = 0; i < 2; i++)
	{
		// clear players spells
		int mana;
		file >> mana;
		players[i]->setMana(mana);
		players[i]->availbleSpells.clear();
		file >> temp;
		for (int j = 0; j < temp; j++)
		{
			int spell;
			file >> spell;
			players[i]->availbleSpells.push_back(Spell(spell));
		}
	}
	// loading BackgroundType
	file >> temp;
	this->setBackground((Background)temp);
	this->backgroud.setTexture(*graphics2.backgroundsTextures[this->backgroundType]);
	return true;
}

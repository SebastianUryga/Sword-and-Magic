#include "pch.h"
#include "PlayerInterface.h"

PlayerInterface* PI = new PlayerInterface();

PlayerInterface::PlayerInterface()
{
	canCalcuatePaths = false;
	end = false;
	gameArea = nullptr;
	currentColorTurn = Color::RED;
}


PlayerInterface::~PlayerInterface()
{
}

int PlayerInterface::getCurrentColor()
{
	return currentColorTurn;
}

void PlayerInterface::select(MP2::ObjectInstance * sel, bool centerView)
{
	Kingdom & player = world.GetKingdom(this->currentColorTurn);
	if (player.containsHero(dynamic_cast<HeroInstance*>(sel)) ||
		player.containsTown(dynamic_cast<TownInstance*>(sel)))
	{
		this->gameArea->selection = sel;
		if (centerView) this->focusOn(sel);
	}
}

void PlayerInterface::focusOn(sf::Vector2f on)
{
	gameArea->focusOn(on);
}

void PlayerInterface::focusOn(sf::Vector2i on, bool fade)
{
	gameArea->focusOn(sf::Vector2f(
		(float)on.x * TILEWIDTH,
		(float)on.y * TILEWIDTH));
}

void PlayerInterface::focusOn(const MP2::ObjectInstance * obj, bool fade)
{
	focusOn(obj->getSightCenter(), fade);
}

void PlayerInterface::calcuatePaths()
{
	HeroInstance* h = nullptr;
	if (h = this->gameArea->curHero())
	{
		h->calcuatePaths();
		PI->canCalcuatePaths = false;
	}
}

void PlayerInterface::mergeStacks(std::vector<Troop> & garr, int stack1Id, int stack2Id) // Mergeing to stack1
{
	garr[stack1Id].count += garr[stack2Id].count;
	garr[stack2Id].monster = Monster::NO_CREATURE;
	garr[stack2Id].count = 0;
}

void PlayerInterface::swapStacks(std::vector<Troop>& garr, int stack1Id, int stack2Id)
{
	std::swap(garr[stack1Id], garr[stack2Id]);
}

void PlayerInterface::tileLClicked(const sf::Vector2i mapPos)
{
	const Maps::Tile *tile = &world.GetTile(mapPos);

	const MP2::ObjectInstance *topBlocking = tile->GetObjectPtr();

	if (topBlocking && mapPos != topBlocking->getVisitablePos()
		&& topBlocking->type == Obj::TOWN &&
		topBlocking->getOwner() == currentColorTurn)
	{
		if (this->gameArea->selection == topBlocking)
			PI->openTownWindow(this->gameArea->curTown());
		else
			this->select(tile->GetObjectPtr());
	}
	
	if (HeroInstance * currentHero = gameArea->curHero()) //hero is selected
	{
		const PathNode *pn = currentHero->pathfinder->getNode(mapPos);
		if (currentHero == topBlocking) //clicked selected hero
		{
			PI->openHeroWindow(currentHero);
			return;
		}
		else if (pn->turns == 255)
		{
			std::cout << "nie osiagalne" << pn->cost << std::endl;
			
			return;
		}
		else
		{
			if (currentHero->currentPath && currentHero->currentPath->endPos() == mapPos)//we'll be moving
			{
				currentHero->moveHero();
				return;
			}
			else //remove old path and find a new one if we clicked on accessible tile
			{
				if (currentHero->makePath(mapPos))
					std::cout << "nowa sciezka" << currentHero->currentPath->endPos().x << " " <<
					currentHero->currentPath->endPos().y << std::endl;
				else
				{
					std::cout << " nie ma nowej sciezki" << std::endl;
					BH.startBallte();
				}
			}
		}
	}
}

void PlayerInterface::tileRClicked(const sf::Vector2i mapPos)
{
	std::shared_ptr<WindowObject> wind;
	wind = std::make_shared<WindowObject>(
		mapPos.x*TILEWIDTH - gameArea->getScrollOffset().x - 100,
		mapPos.y*TILEWIDTH - gameArea->getScrollOffset().y - 100,
		100, 100, GH.globalFont);
	if (auto obj = world.GetTile(mapPos).GetObjectPtr())
	{
		if (obj->type == Obj::HERO)
		{
			// show small Hero Window

		}
		else if (obj->type == Obj::TOWN)
		{
			// show small Town window
		}
		else
		{
			std::string text = obj->getHoverText(gameArea->curHero());
			wind->addText(text, sf::Vector2f(10, 10));
		}
	}
	else
	{
		std::string text = Maps::Ground::String(world.GetTile(mapPos).GetGround());
		wind->addText(text, sf::Vector2f(10, 10));
	}

	GH.makePopup(wind);
}

void PlayerInterface::dismissHero(HeroInstance * hero)
{
	std::cout << "kiled hero" <<hero->id<< std::endl;
	//remove from map
	// set owner to unused
	
}

void PlayerInterface::openHeroWindow(HeroInstance * hero)
{
	GH.pushWindowT<HeroWindow>(hero);
}

void PlayerInterface::openTownWindow(TownInstance * town)
{
	GH.pushWindowT<TownWindow>(town);
}

void PlayerInterface::openWindow(int player, const MP2::ObjectInstance* tav)
{
	GH.pushWindowT<TavernWindow>(player,tav);
}

bool PlayerInterface::canRecruitHero(int player, const MP2::ObjectInstance * obj)
{
	Kingdom & playerKingdom = world.GetKingdom(player);

	if (playerKingdom.heroes.size() > 8)
		return false;
	// check if enough gold
	if (playerKingdom.getMoney() < 2500)
		return false;
	// check if tile is allready busy
	if(world.GetTile(obj->getVisitablePos()).GetObjectPtr()->type == Obj::HERO)
		return false;

	return true;
}

HeroInstance * PlayerInterface::getTavernHero(int player)
{
	HeroInstance * h = world.getRandomHero();
	return h;
}

void PlayerInterface::bulid(BuildingID building, int slot)
{
	TownInstance* town = gameArea->curTown();
	if (town)
	{
		world.GetKingdom(currentColorTurn).spendMoney(buildingStats[building].cost);
		if (slot < 6)
			town->buldings[slot]->setType(building);
		else
		{
			town->fortification->setType(building);
		}
	}
}

void PlayerInterface::nextPlayer()
{
	this->currentColorTurn = Color::getNextColor(this->currentColorTurn);
	if (this->currentColorTurn == Color::GREEN)
		this->currentColorTurn = Color::RED;

	Kingdom & player = world.GetKingdom(this->currentColorTurn);
	this->gameArea->playerListOfHero->setHeroes(player.heroes);
}

void PlayerInterface::tileLClickedEditor(const sf::Vector2i mapPos)
{
}

void PlayerInterface::showYesNoDialog(const std::string & text, std::function<void()> onYes, std::function<void()> onNo)
{
	//do testu
	std::shared_ptr<WindowObject> temp =
		std::make_shared<WindowObject>(300, 200, 400, 400, GH.globalFont);
	temp->buttons["yes"] = std::make_shared<Button>(
		100 + 300, 300 + 200, 50, 30, &GH.globalFont, "Yes",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200)
		);
	temp->buttons["no"] = std::make_shared<Button>(
		300 + 300, 300 + 200, 50, 30, &GH.globalFont, "No",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200)
		);
	temp->buttons["no"]->addFuctionallity([=]() {onNo(); temp->close(); });
	temp->buttons["yes"]->addFuctionallity([=]() {onYes(); temp->close(); });
	temp->interactiveElem.push_back(temp->buttons["no"]);
	temp->interactiveElem.push_back(temp->buttons["yes"]);
	temp->texts.push_back(sf::Text(text,GH.globalFont,20));
	temp->texts[0].setPosition(50 + 300, 50 + 200);
	temp->background.setOutlineThickness(2);
	temp->background.setOutlineColor(sf::Color::Yellow);
	GH.pushWindow(temp);
}

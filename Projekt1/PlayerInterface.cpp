#include "pch.h"
#include "PlayerInterface.h"

PlayerInterface* PI = new PlayerInterface();

PlayerInterface::PlayerInterface()
{
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
					std::cout << " nie ma nowej sciezki" << std::endl;
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

void PlayerInterface::openWindow(int player, const MP2::ObjectInstance* tav)
{
	GH.pushWindowT<TavernWindow>(player,tav);
}

bool PlayerInterface::canRecruitHero(int player, const MP2::ObjectInstance * obj)
{
	// check if enough gold
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

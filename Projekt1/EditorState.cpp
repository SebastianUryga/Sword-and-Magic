#include "pch.h"
#include "EditorState.h"


void EditorState::initView()
{
	this->view.setSize(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	);
	this->view.setCenter(
		this->window->getSize().x / 2.f,
		this->window->getSize().y / 2.f
	);
}

void EditorState::initBackground()
{
}

void EditorState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["CHANGE_ARENA_OBJ"] = this->supportedKeys->at("A");
	this->keybinds["CHANGE_MOUNTS_OBJ"] = this->supportedKeys->at("M");
	this->keybinds["CHANGE_STABLE_OBJ"] = this->supportedKeys->at("S");
	this->keybinds["CHANGE_CRATER_OBJ"] = this->supportedKeys->at("C");
	this->keybinds["CHANGE_HERO_OBJ"] = this->supportedKeys->at("H");
	this->keybinds["CHANGE_TRADING_POST_OBJ"] = this->supportedKeys->at("T");
	this->keybinds["CHANGE_POS_MODE"] = this->supportedKeys->at("P");
	this->keybinds["CHANGE_TOWN_OBJ"] = this->supportedKeys->at("Q");
	this->keybinds["CHANGE_ROADS_MODE"] = this->supportedKeys->at("R");
	this->keybinds["ERASE_MODE"] = this->supportedKeys->at("E");
}

void EditorState::initButtons()
{
	this->buttons["LOAD_BTN"] = new Button(0, 0, 250, 50,
		this->font, "Load",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
	this->buttons["SAVE_BTN"] = new Button(0, 50, 250, 50,
		this->font, "Save",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
}

void EditorState::initWorld()
{
	if (!world.load("startmap.txt"))
		world.NewMaps(90, 60);
}

void EditorState::initGameArea()
{
	std::shared_ptr<Interface::GameArea> area;
	area = std::make_shared< Interface::GameArea>();
	area->built(this->window, Interface::EditorMode);
	PI->gameArea = area;
	GH.pushWindow(area);
}

EditorState::EditorState(StateData * stateData)
	: State(stateData)
{
	this->initView();
	this->initBackground();
	this->initKeybinds();

	this->initButtons();
	this->initWorld();
	this->initGameArea();
	this->chosenTypeObj = Obj::NO_OBJ;
}

EditorState::~EditorState()
{
	for (auto i : this->buttons)
		delete i.second;
	world.Reset();
}

void EditorState::OnMouseLeftButtonClick()
{
	sf::Vector2i mousePos = this->mousePosTile;

	mousePos += PI->gameArea->getScrollTileOffset();
	//mousePos.x += (int)PI->gameArea->getScrollOffset().x / TILEWIDTH;
	std::cout << mousePos.x << " " << mousePos.y << std::endl;
	
	if (Interface::GetGameArea().contains( mousePos ))
	{
		sf::Vector2i tile = mousePos;
		if (mode == Mode::PutObject)
		{
			MP2::ObjectInstance* obj = nullptr;
			switch (chosenTypeObj)
			{
			case Obj::HERO:
			{
				auto hero = new HeroInstance();
				
				hero = world.getRandomHero(); // temp code
				hero->setOwner(PI->getCurrentColor()); // temporary code
				obj = hero;
				break;
			}
			case Obj::TOWN:
			{
				auto town = new TownInstance();
				town->setOwner(PI->getCurrentColor());
				town->putBuildingsOnMap(tile);
				obj = town;
				break;
			}
			case Obj::ARTIFACT:
				//auto art = new ArtifactInstance();
				//obj = art;
			case Obj::MONSTER:
				//auto creature = CreatureInstance();
				//obj = creature;
			case Obj::RESOURCE:
				//auto res = ResourseInstance();
				//obj = res;
			default:
				obj = new MP2::ObjectInstance();
				break;
			}
			obj->setType(chosenTypeObj);
			obj->setTilePos(tile);
			obj->initObj();
			world.addMapObject(obj);
		}
		if (mode == Mode::Erase)
		{
			world.removeMapObject(tile);
			this->settingRoad = true;
		}
		if (mode == Mode::ChangePos)
		{
			this->selection = world.GetObjectByPos(tile);
		}
		if (mode == Mode::MakeRoads)
		{
			this->settingRoad = true;	
		}
	}

}

void EditorState::OnMouseLeftButtonReleased()
{
	if (selection && mode == Mode::ChangePos)
	{
		std::cout << "button rleased." << std::endl;
		world.changeObjPos(
			this->selection->id,
			this->selection->pos,
			this->mousePosTile + PI->gameArea->getScrollTileOffset());
		this->selection = nullptr;
	}
	this->settingRoad = false;
}

// Functions

void EditorState::endState()
{
	State::endState();
	GH.topWindow()->close();
	world.Reset();
}

void EditorState::updateRoadSettingMode()
{
	if (this->mouseMoved && this->settingRoad)
	{
		sf::Vector2i mousePos = 
			this->mousePosTile + PI->gameArea->getScrollTileOffset();
		Maps::Tile & tile = world.GetTile(mousePos);
			
		tile.SetRoad(this->chosenRoadType);
	}
	
}

void EditorState::updateSelectObj()
{

	if (this->selection && mode == Mode::ChangePos && this->mouseMoved)
	{
		this->selection->sprite.setPosition(
			sf::Vector2f(
				((sf::Vector2f)this->mousePosTile) * TILEWIDTH)
		);
	}

}

void EditorState::updateButtons()
{
	/* update all the buttons and hendles thier functionalaity*/
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	if (this->buttons["LOAD_BTN"]->isPressed() && this->getKeytime())
	{
		world.Reset();
		world.load("startmap.txt");
	}
	if (this->buttons["SAVE_BTN"]->isPressed() && this->getKeytime())
	{
		world.save("startmap.txt");
	}
}


void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"])))
		endState();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_MOUNTS_OBJ"])))
	{
		mode = Mode::PutObject;
		chosenTypeObj = Obj::MOUNTS;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_STABLE_OBJ"])))
	{
		mode = Mode::PutObject;
		chosenTypeObj = Obj::STABLES;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_CRATER_OBJ"])))
	{
		mode = Mode::PutObject;
		chosenTypeObj = Obj::TAVERN; // to change on Crater
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_ARENA_OBJ"])))
	{
		mode = Mode::PutObject;
		chosenTypeObj = Obj::ARENA;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_TRADING_POST_OBJ"])))
	{
		mode = Mode::PutObject;
		chosenTypeObj = Obj::TRADING_POST;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_HERO_OBJ"])))
	{
		mode = Mode::PutObject;
		chosenTypeObj = Obj::HERO;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_ROADS_MODE"])))
	{
		this->mode = Mode::MakeRoads;
		this->chosenRoadType = Maps::RoadType::COBBLESTONE_ROAD;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_TOWN_OBJ"])))
	{
		mode = Mode::PutObject;
		chosenTypeObj = Obj::TOWN;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CHANGE_POS_MODE"])))
	{
		mode = Mode::ChangePos;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["ERASE_MODE"])))
	{
		mode = Mode::Erase;
		chosenRoadType = Maps::RoadType::NO_ROAD;
	}

}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateInput(dt);
	this->updateKeytime(dt);
	this->updateSelectObj();
	this->updateRoadSettingMode();
	Interface::GetGameArea().update(dt, this->mousePosWindow);
	this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget* target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
	
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	Interface::GetGameArea().render(target);
	this->renderButtons(target);
}

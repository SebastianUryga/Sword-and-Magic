#include "pch.h"
#include "GameState.h"



void GameState::initView()
{
	
}

void GameState::initTextutres()
{
	
}

void GameState::initKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

void GameState::initPlayers()
{
	//this->hero = new Hero(*graphics.heroOnMap);
	for (auto & h : world.vec_heros)
	{
		h->pathfinder->initializeGraph();
		this->calculatePaths(h);
	}
		
}

void GameState::initWorld()
{

	if (!world.load("startmap.txt"))
		world.NewMaps(30, 20);	
}

void GameState::initGameArea()
{
	std::shared_ptr<Interface::GameArea> area;
	area = std::make_shared<Interface::GameArea>();
	area->built(this->window, Interface::EditorMode);
	PI->gameArea = area;
	GH.pushInt(area);
}

void GameState::initButtonsArea()
{
	Interface::GetButtonsArea().built(sf::Vector2f(0, 0), *this->font, this->window);
}

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initView();
	this->initKeybinds();
	this->initTextutres();

	this->initWorld();
	this->initPlayers();
	this->initGameArea();
	this->initButtonsArea();
	
}

GameState::~GameState()
{
	world.Reset();
	//GH.popInt(std::shared_ptr<Interface::GameArea>(&Interface::GetGameArea()));
}

//modifires
void GameState::setCurrentColor(int color)
{
	this->currentColorTurn = color;
	//world.GetKingdom(color).setActualTrun(true);
}

void GameState::setToNextColor()
{
	// do testu
	this->setCurrentColor(this->currentColorTurn << 1);
}

void GameState::OnMouseLeftButtonClick()
{
	//if(GH.)
	sf::Vector2i mousePos((int)this->mousePosView.x, (int)this->mousePosView.y);
	if (Interface::GetGameArea().contains(mousePos))
	{
		sf::Vector2i mapPos(mousePos.x / (int)TILEWIDTH, mousePos.y / (int)TILEWIDTH);
		if (mapPos != this->mousePosTile)
			std::cout << "nie zgadza sie o " << mapPos.x - mousePosTile.x << std::endl;
		Interface::MouseCursorAreaClickLeft(mousePos);
		
		//std::cout<< tile.x <<" "<<tile.y <<std::endl;
	}
}

void GameState::endState()
{
	State::endState();
	GH.topInt()->close();
}

// Functions

void GameState::calculatePaths(const HeroInstance * hero)
{
	hero->pathfinder->calculatePaths();
}

void GameState::updateView()
{
}

void GameState::updateEvents()
{
	
}

void GameState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"])) && this->getKeytime())
		this->endState();

}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateKeytime(dt);
	//Interface::GetGameArea().update(dt, this->mousePosWindow);
	this->updateView();

	Interface::GetButtonsArea().update(this->mousePosWindow);
	if (GH.empty())
		return;
	GH.topInt()->update(dt,this->mousePosWindow);
	
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//PI->gameArea->render(target,Color::RED);
	
	
	if (GH.empty())
		return;
	GH.topInt()->render(target);
	Interface::GetButtonsArea().render(target);
	// if () window.setView(gameArea.view);
}

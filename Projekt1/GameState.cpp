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
	PI->canCalcuatePaths = true;
}

void GameState::initWorld()
{

	if (!world.load("startmap.txt"))
		world.NewMaps(90, 60);
}

void GameState::initGameArea()
{
	std::shared_ptr<Interface::GameArea> area;
	area = std::make_shared<Interface::GameArea>();
	area->built(this->window, Interface::GameMode);
	PI->gameArea = area;
	GH.pushWindow(area);
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
	this->initGameArea();
	this->initPlayers();
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
	if(GH.topWindow() == PI->gameArea)
	if (Interface::GetGameArea().contains(this->mousePosWindow))
	{
		Interface::MouseCursorAreaClickLeft(this->mousePosTile);
	}
}

void GameState::OnMouseRightButtonClick()
{
	if(GH.topWindow() == PI->gameArea)
		if (Interface::GetGameArea().contains(this->mousePosWindow))
		{
			Interface::MouseCursorAreaClickRight(this->mousePosTile);
		}
}

void GameState::endState()
{
	State::endState();
	GH.topWindow()->close();
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
	this->updateMousePositions(&Interface::GetGameArea().getView());
	this->updateInput(dt);
	this->updateKeytime(dt);
	
	this->updateView();

	Interface::GetButtonsArea().update(this->mousePosWindow);
	if (GH.empty())
		return;
	
	GH.topWindow()->update(dt,this->mousePosWindow);
	
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//PI->gameArea->render(target,Color::RED);
	
	
	if (GH.empty())
		return;
	GH.renderAll(target);
	Interface::GetButtonsArea().render(target);
	// if () window.setView(gameArea.view);
}

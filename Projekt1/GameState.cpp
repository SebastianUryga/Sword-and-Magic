#include "pch.h"
#include "GameState.h"



void GameState::initView()
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
	Interface::GameArea & area = Interface::GetGameArea();

	area.built(this->window, Interface::GameMode);
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
		sf::Vector2i mapPos(mousePos.x / (int)TILEWIDTH, mousePos.y / TILEWIDTH);
		if (mapPos != this->mousePosTile)
			std::cout << "nie zgadza sie o " << mapPos.x - mousePosTile.x << std::endl;
		Interface::MouseCursorAreaClickLeft(mousePos);
		
		//std::cout<< tile.x <<" "<<tile.y <<std::endl;
	}
}

// Functions

void GameState::calculatePaths(const HeroInstance * hero)
{
	hero->pathfinder->calculatePaths();
}

void GameState::updateView()
{
	if (Interface::GetGameArea().needScroll())
	{
		this->view.move(
			(float)Interface::GetGameArea().getScrollOffset().x*TILEWIDTH,
			(float)Interface::GetGameArea().getScrollOffset().y*TILEWIDTH
		);
	}
}

void GameState::updateEvents()
{
	
}

void GameState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["SCROLL_DOWN"])) && this->getKeytime())
		//Interface::GetGameArea().needToScroll.y += 1;
		view.move(0, 32.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["SCROLL_UP"])) && this->getKeytime())
		//Interface::GetGameArea().needToScroll.y -= 1;
		view.move(0, -32.f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"])) && this->getKeytime())
		this->endState();

}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateInput(dt);
	this->updateKeytime(dt);
	Interface::GetGameArea().update(dt, this->mousePosWindow,this->currentColorTurn);
	this->updateView();
	//this->hero->update(dt);
	Interface::GetButtonsArea().update(this->mousePosWindow);
	GH.update(this->mousePosWindow);
	
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
	Interface::GetGameArea().render(target,Color::RED);
	
	//this->hero->render(target);
	target->setView(this->window->getDefaultView());
	Interface::GetButtonsArea().render(target);

	// if () window.setView(gameArea.view);
}

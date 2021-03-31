#include "pch.h"
#include "Game.h"
#include "GuiHandler.h"
//Static  Functions

//Initializer functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode() , "Heroes 3",sf::Style::Default);
	this->window->setFramerateLimit(120);

}

void Game::initFonts()
{
	this->font = new sf::Font();
	if (!this->font->loadFromFile("Fonts\\bigfonts.ttf"))
	{
		throw("ERROR::MAINMENUSTATE:: COULD NOT LOAD FONT");
	}
	GH.globalFont = *this->font;
}

void Game::initKeys()
{
	this->supportedKeys["Escape"] = sf::Keyboard::Escape;
	this->supportedKeys["A"] = sf::Keyboard::A;
	this->supportedKeys["D"] = sf::Keyboard::D;
	this->supportedKeys["S"] = sf::Keyboard::S;
	this->supportedKeys["W"] = sf::Keyboard::W;
	this->supportedKeys["U"] = sf::Keyboard::U;
	this->supportedKeys["J"] = sf::Keyboard::J;
	this->supportedKeys["C"] = sf::Keyboard::C;
	this->supportedKeys["E"] = sf::Keyboard::E;
	this->supportedKeys["H"] = sf::Keyboard::H;
	this->supportedKeys["P"] = sf::Keyboard::P;
	this->supportedKeys["T"] = sf::Keyboard::T;
	this->supportedKeys["M"] = sf::Keyboard::M;
	this->supportedKeys["B"] = sf::Keyboard::B;
	this->supportedKeys["Q"] = sf::Keyboard::Q;
	this->supportedKeys["R"] = sf::Keyboard::R;
	this->supportedKeys["U"] = sf::Keyboard::U;
	this->supportedKeys["Y"] = sf::Keyboard::Y;
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.states = &this->states;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.font = this->font;
}

void Game::initState()
{
	this->states.push(new MainMenuState(&this->stateData));
}

void Game::initTextures()
{
	graphics.Init();
}


Game::Game()
{
	this->initWindow();
	this->initFonts();
	this->initTextures();
	this->initKeys();
	this->initStateData();
	this->initState();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

// Functions

void Game::endApplication()
{
	std::cout << "Ending Application!" << std::endl;
}

void Game::render()
{
	this->window->clear();
	
	// render items
	if (!states.empty())
		states.top()->render();

	this->window->display();
}

//update

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
	if (PI)
		PI->globalClock.restart(); // temporary code
}

void Game::updateEvents()
{
	GH.handleEvents(states, this->window, this->sfEvent);
}

void Game::update()
{
	this->updateEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			delete this->states.top();
			this->states.pop();
		}
	}
	// Applicatin end
	else
	{
		this->endApplication();
		this->window->close();
	}	
}

void Game::run()
{
	while (this->window->isOpen())
	{
		updateDt();
		update();
		if (PI) if (PI->globalClock.getElapsedTime().asSeconds() > 0.1)
			std::cout <<"update"<< PI->globalClock.getElapsedTime().asSeconds()<< std::endl;
		//std::cout <<"update:"<< dtClock.getElapsedTime().asSeconds() << std::endl;
		render();
		//if (PI) if ( PI->globalClock.getElapsedTime().asSeconds()  > 0.1)
			//std::cout << "render" << PI->globalClock.getElapsedTime().asSeconds() << std::endl;
		//if(dtClock.getElapsedTime().asSeconds() > 0.09)
		//std::cout << "render:" << dtClock.getElapsedTime().asSeconds() << std::endl;
	}
}

#include "pch.h"
#include "Game.h"
#include "GuiHandler.h"
//Static  Functions

//Initializer functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode() , "blablabla",sf::Style::Default);
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
}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (this->sfEvent.type == sf::Event::MouseButtonPressed &&
			sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->states.top()->OnMouseLeftButtonClick();
			
		}
		if (this->sfEvent.type == sf::Event::MouseButtonReleased)
		{
			this->states.top()->OnMouseLeftButtonReleased();
		}
		if (this->sfEvent.type == sf::Event::MouseButtonPressed &&
			sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			this->states.top()->OnMouseRightButtonClick();
		}
	}
}

void Game::update()
{
	this->updateEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
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
		render();
	}
}

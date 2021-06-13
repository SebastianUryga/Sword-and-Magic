#include "pch.h"
#include "GuiHandler.h"

//Initializer functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Heroes 3", sf::Style::Default);
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

void Game::initTextures()
{
	graphics.Init();
}

Game::Game()
{
	this->initWindow();
	this->initFonts();
	this->mainMenuState();
	this->initTextures();
}


Game::~Game()
{
	delete this->window;
}

// Functions

void Game::mainMenuState()
{
	std::shared_ptr<WindowObject> mainMenu = std::make_shared<WindowObject>(
		(float)this->window->getPosition().x,
		(float)this->window->getPosition().y,
		this->window->getSize().x,
		this->window->getSize().y, *this->font);

	mainMenu->background.setTexture(graphics.menuBackgroud.get());

	mainMenu->buttons["GAME_STATE_BTN"] = std::make_shared<Button>(
		300, 280, 250, 50,
		this->font, "New Game");
	mainMenu->buttons["SETTINGS_STATE_BTN"] = std::make_shared<Button>(
		300, 380, 250, 50,
		this->font, "Settings");
	mainMenu->buttons["EDITOR_STATE_BTN"] = std::make_shared<Button>(
		300, 480, 250, 50,
		this->font, "EDITOR");
	mainMenu->buttons["EXIT_GAME"] = std::make_shared<Button>(
		300, 680, 250, 50,
		this->font, "Quit");

	mainMenu->buttons["GAME_STATE_BTN"]->addFuctionallity([=]()
	{
		this->gameState();
	});
	mainMenu->buttons["SETTINGS_STATE_BTN"]->addFuctionallity([=]()
	{
		this->settingState();
	});
	mainMenu->buttons["EDITOR_STATE_BTN"]->addFuctionallity([=]()
	{
		this->editorState();
	});
	mainMenu->buttons["EXIT_GAME"]->addFuctionallity([=]()
	{
		GH.popWindow(mainMenu);
	});
	for (auto& btn : mainMenu->buttons)
		mainMenu->interactiveElem.push_back(btn.second);

	GH.pushWindow(mainMenu);
}

void Game::settingState()
{
	std::shared_ptr<WindowObject> settingMenu = std::make_shared<WindowObject>(
		(float)this->window->getPosition().x,
		(float)this->window->getPosition().y,
		this->window->getSize().x,
		this->window->getSize().y, *this->font);

	settingMenu->background.setTexture(graphics.menuBackgroud.get());

	settingMenu->buttons["EXIT_GAME"] = std::make_shared<Button>(
		300, 680, 250, 50,
		this->font, "Quit");

	settingMenu->buttons["EXIT_GAME"]->addFuctionallity([=]()
	{
		GH.popWindow(settingMenu);
	});
	settingMenu->interactiveElem.push_back(settingMenu->buttons["EXIT_GAME"]);

	GH.pushWindow(settingMenu);
}

void Game::gameState()
{
	BH.startBallte();
}

void Game::editorState()
{
	auto battlefield = std::make_shared<Battlefield>(GameMode::Editor);
	battlefield->interactiveElem.push_back(battlefield);
	GH.pushWindow(battlefield);

}

void Game::endApplication()
{
	std::cout << "Ending Application!" << std::endl;
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateEvents()
{
	if (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			window->close();
		}
		if (sfEvent.type == sf::Event::KeyPressed || sfEvent.type == sf::Event::KeyReleased)
		{

		}

		if (sfEvent.type == sf::Event::MouseMoved)
		{
			GH.handleMouseMotion();
		}
		if (sfEvent.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				GH.handleMouseButtonClick(sf::Mouse::Left, true);
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				GH.handleMouseButtonClick(sf::Mouse::Right, true);
			}
		}
	
		if (sfEvent.type == sf::Event::MouseButtonReleased)
		{
			GH.handleMouseButtonClick(sf::Mouse::Left, false);
			GH.handleMouseButtonClick(sf::Mouse::Right, false);
		}
		GH.mousePosWindow = (sf::Vector2f)sf::Mouse::getPosition(*window);
	}
}

void Game::update()
{
	if (!GH.empty())
	{
		this->updateEvents();
		GH.update(dt);
	}
	// Applicatin end
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	// render items
	GH.render(this->window);
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
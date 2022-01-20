#include "Game.h"

//Initializer functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(),  "Heroes 3",
		 sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(120);
	Config.windowSize = this->window->getSize();

}

void Game::initFonts()
{
	this->font = new sf::Font();
	if (!this->font->loadFromFile("Fonts/Alice_in_Wonderland_3.ttf"))
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
	//graphics.Init();
	graphics2.init();
}

Game::Game()
{
	this->initWindow();
	Config.load();
	this->initFonts();
	this->initTextures();
	this->mainMenuState();
}

Game::~Game()
{
	delete this->window;
	delete this->font;
}

// Functions

void Game::mainMenuState()
{
	std::shared_ptr<WindowObject> mainMenu = std::make_shared<WindowObject>(
		(float)this->window->getPosition().x,
		(float)this->window->getPosition().y,
		this->window->getSize().x,
		this->window->getSize().y,
		*this->font);

	mainMenu->background.setTexture(graphics.menuBackgroud.get());

	mainMenu->buttons["GAME_STATE_BTN"] = std::make_shared<Button>(
		300, 280, 250, 50, this->font, "New Game");
	mainMenu->buttons["SETTINGS_STATE_BTN"] = std::make_shared<Button>(
		300, 380, 250, 50, this->font, "Settings");
	mainMenu->buttons["EDITOR_STATE_BTN"] = std::make_shared<Button>(
		300, 480, 250, 50, this->font, "Editor");
	mainMenu->buttons["EXIT_GAME"] = std::make_shared<Button>(
		300, 680, 250, 50, this->font, "Quit");

	mainMenu->buttons["GAME_STATE_BTN"]->addFuctionallity([=]() {
		this->gameState();
	});
	mainMenu->buttons["SETTINGS_STATE_BTN"]->addFuctionallity([=]() {
		this->settingState();
	});
	mainMenu->buttons["EDITOR_STATE_BTN"]->addFuctionallity([=]() {
		this->editorState();
	});
	mainMenu->buttons["EXIT_GAME"]->addFuctionallity([=]() {
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
		this->window->getSize().y,
		*this->font);

	auto marker = std::make_shared<sf::Text>("->",GH.globalFont,30);
	if (Config.battlefiledTileHegiht == 20 && Config.battlefiledTileWidth == 50)
		marker->setPosition(160, 280);
	else if (Config.battlefiledTileHegiht == 26 && Config.battlefiledTileWidth == 60)
		marker->setPosition(160, 350);
	else if (Config.battlefiledTileHegiht == 34 && Config.battlefiledTileWidth == 70)
		marker->setPosition(160, 420);
	else
		marker->setPosition(-1000, -1000);
	settingMenu->texts.push_back(marker);
	
	settingMenu->background.setTexture(graphics.menuBackgroud.get());
	settingMenu->addText("Select battle size in tiles", sf::Vector2f(200, 240));
	settingMenu->buttons["SizeOption1"] = std::make_shared<Button>(
		200, 280, 250, 50, this->font, "50 x 20");
	settingMenu->buttons["SizeOption2"] = std::make_shared<Button>(
		200, 350, 250, 50, this->font, "60 x 26");
	settingMenu->buttons["SizeOption3"] = std::make_shared<Button>(
		200, 420, 250, 50, this->font, "70 x 34");


	settingMenu->buttons["EXIT_GAME"] = std::make_shared<Button>(
		300, 680, 250, 50, this->font, "Quit");

	settingMenu->buttons["EXIT_GAME"]->addFuctionallity([=]() {
		GH.popWindow(settingMenu);
	});
	settingMenu->buttons["SizeOption1"]->addFuctionallity([=]() {
		Config.battlefiledTileWidth = 50;
		Config.battlefiledTileHegiht = 20;
		marker->setPosition(160, 280);
		Config.save();
	});
	settingMenu->buttons["SizeOption2"]->addFuctionallity([=]() {
		Config.battlefiledTileWidth = 60;
		Config.battlefiledTileHegiht = 26;
		marker->setPosition(160, 350);
		Config.save();
	});
	settingMenu->buttons["SizeOption3"]->addFuctionallity([=]() {
		Config.battlefiledTileWidth = 70;
		Config.battlefiledTileHegiht = 34;
		marker->setPosition(160, 420);
		Config.save();
	});
	for(auto button : settingMenu->buttons)
		settingMenu->interactiveElem.push_back(button.second);
	GH.pushWindow(settingMenu);
}

void Game::gameState()
{
	BH.startBallte();
}

void Game::editorState()
{
	auto battlefield = std::make_shared<Battlefield>(GameMode::Editor);
	battlefield->load("startMap.txt");
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
	while (window->pollEvent(sfEvent))
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
		
	}
}

void Game::updateMousePos()
{
	GH.mousePosWindow = (sf::Vector2f)sf::Mouse::getPosition(*window);
	GH.mousePosWindow.x /= ((float)window->getSize().x / sf::VideoMode::getDesktopMode().width);
	GH.mousePosWindow.y /= ((float)window->getSize().y / sf::VideoMode::getDesktopMode().height);

	GH.mouseTilePos = (sf::Vector2i)(sf::Vector2f(
		(GH.mousePosWindow.x - Config.battlefieldOffset.x) / Config.tileWidth,
		(GH.mousePosWindow.y - Config.battlefieldOffset.y) / Config.tileHeight));
}

void Game::update()
{
	if (!GH.empty())
	{
		this->updateEvents();
		this->updateMousePos();
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
	sf::Clock measureTime;
	while (this->window->isOpen())
	{

		this->updateDt();
		this->update();
		//std::cout << "Time Looptick update : " << measureTime.restart().asMilliseconds() << std::endl;

		this->render();
		//std::cout << "Time Looptick render: " << measureTime.restart().asMilliseconds() <<std::endl;

	}
}
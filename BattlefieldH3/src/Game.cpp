#include "Game.h"

//Initializer functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(),  "Open Arena of Swords and Magic",
		 sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(120);
	Config.windowSize = this->window->getSize();

}

void Game::initFonts()
{
	this->font = new sf::Font();
	if (!this->font->loadFromFile("res/Fonts/Alice_in_Wonderland_3.ttf"))
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

void Game::refresh()
{

}

Game::Game()
{
	this->initWindow();
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

	auto text = std::make_shared<sf::Text>("Open Arena of Swords and Magic", *this->font, 60);
	text->setPosition(sf::Vector2f(500, 80));

	mainMenu->background.setTexture(graphics.menuBackgroud.get());

	mainMenu->buttons["CAMPAIN_STATE_BTN"] = std::make_shared<Button>(
		300, 180, 250, 50, this->font, "Campain");
	mainMenu->buttons["GAME_STATE_BTN"] = std::make_shared<Button>(
		300, 280, 250, 50, this->font, "Start Custom Game");
	mainMenu->buttons["SETTINGS_STATE_BTN"] = std::make_shared<Button>(
		300, 380, 250, 50, this->font, "Settings");
	mainMenu->buttons["EDITOR_STATE_BTN"] = std::make_shared<Button>(
		300, 480, 250, 50, this->font, "Edit Custom Game");
	mainMenu->buttons["EXIT_GAME"] = std::make_shared<Button>(
		300, 620, 250, 50, this->font, "Quit");

	mainMenu->buttons["CAMPAIN_STATE_BTN"]->addFuctionallity([=]() {
		this->campainState();
	}); 
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

	mainMenu->texts.push_back(text);
	mainMenu->onActive = []() {
		std::fstream file;
		file.open("res/config.txt");
		Config.load(file, false);
		file.close();
	};
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

	// Battle size settings
	auto marker = std::make_shared<sf::Text>("->",GH.globalFont,30);
	if (Config.battlefiledTileHegiht == 20 && Config.battlefiledTileWidth == 50)
		marker->setPosition(260, 280);
	else if (Config.battlefiledTileHegiht == 26 && Config.battlefiledTileWidth == 60)
		marker->setPosition(260, 350);
	else if (Config.battlefiledTileHegiht == 34 && Config.battlefiledTileWidth == 70)
		marker->setPosition(260, 420);
	else
		marker->setPosition(-1000, -1000);
	settingMenu->texts.push_back(marker);
	
	settingMenu->background.setTexture(graphics.menuBackgroud.get());
	settingMenu->addText("Select battle size in tiles", sf::Vector2f(300, 240));
	settingMenu->buttons["SizeOption1"] = std::make_shared<Button>(
		300, 280, 250, 50, this->font, "50 x 20");
	settingMenu->buttons["SizeOption2"] = std::make_shared<Button>(
		300, 350, 250, 50, this->font, "60 x 26");
	settingMenu->buttons["SizeOption3"] = std::make_shared<Button>(
		300, 420, 250, 50, this->font, "70 x 34");


	settingMenu->buttons["SizeOption1"]->addFuctionallity([=]() {
		Config.battlefiledTileWidth = 50;
		Config.battlefiledTileHegiht = 20;
		marker->setPosition(260, 280);
		Config.save("res/config.txt");
	});
	settingMenu->buttons["SizeOption2"]->addFuctionallity([=]() {
		Config.battlefiledTileWidth = 60;
		Config.battlefiledTileHegiht = 26;
		marker->setPosition(260, 350);
		Config.save("res/config.txt");
	});
	settingMenu->buttons["SizeOption3"]->addFuctionallity([=]() {
		Config.battlefiledTileWidth = 70;
		Config.battlefiledTileHegiht = 34;
		marker->setPosition(260, 420);
		Config.save("res/config.txt");
	});

	// PvP settings
	/*auto marker2 = std::make_shared<sf::Text>("->", GH.globalFont, 30);
	if (Config.PvP)
		marker2->setPosition(560, 280);
	else 
		marker2->setPosition(560, 350);
	settingMenu->texts.push_back(marker2);

	settingMenu->addText("Choose Game Mode", sf::Vector2f(600, 240));
	settingMenu->buttons["ModeOption1"] = std::make_shared<Button>(
		600, 280, 250, 50, this->font, "Player vs Player");
	settingMenu->buttons["ModeOption2"] = std::make_shared<Button>(
		600, 350, 250, 50, this->font, "Player vs AI");

	settingMenu->buttons["ModeOption1"]->addFuctionallity([=]() {
		Config.PvP = true;
		marker2->setPosition(560, 280);
		Config.save("res/config.txt");
	});
	settingMenu->buttons["ModeOption2"]->addFuctionallity([=]() {
		Config.PvP = false;
		marker2->setPosition(560, 350);
		Config.save("res/config.txt");
	});*/

	settingMenu->buttons["Back"] = std::make_shared<Button>(
		300, 680, 250, 50, this->font, "Back");

	settingMenu->buttons["Back"]->addFuctionallity([=]() {
		GH.popWindow(settingMenu);
	});
	
	for(auto button : settingMenu->buttons)
		settingMenu->interactiveElem.push_back(button.second);
	GH.pushWindow(settingMenu);
}

void Game::gameState()
{
	BH.startBallte("res/startMap.txt");
}

void Game::campainState()
{
	std::shared_ptr<WindowObject> campainMenu = std::make_shared<WindowObject>(
		(float)this->window->getPosition().x,
		(float)this->window->getPosition().y,
		this->window->getSize().x,
		this->window->getSize().y,
		*this->font);

	campainMenu->addText("Choose Level", sf::Vector2f(300, 240));
	campainMenu->buttons["Level1"] = std::make_shared<Button>(
		300, 280, 250, 50, this->font, "Level 1");
	campainMenu->buttons["Level2"] = std::make_shared<Button>(
		300, 350, 250, 50, this->font, "Level 2");
	campainMenu->buttons["Level3"] = std::make_shared<Button>(
		300, 420, 250, 50, this->font, "Level 3");
	campainMenu->buttons["Level4"] = std::make_shared<Button>(
		300, 490, 250, 50, this->font, "Level 4");
	campainMenu->buttons["Level5"] = std::make_shared<Button>(
		300, 560, 250, 50, this->font, "Level 5");
	campainMenu->buttons["Level6"] = std::make_shared<Button>(
		600, 280, 250, 50, this->font, "Level 6");
	campainMenu->buttons["Level7"] = std::make_shared<Button>(
		600, 350, 250, 50, this->font, "Level 7");
	campainMenu->buttons["Level8"] = std::make_shared<Button>(
		600, 420, 250, 50, this->font, "Level 8");
	campainMenu->buttons["Level9"] = std::make_shared<Button>(
		600, 490, 250, 50, this->font, "Level 9");

	campainMenu->buttons["Level1"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level1.txt");
		BH.battlefield->level = 1;
	});
	campainMenu->buttons["Level2"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level2.txt");
		BH.battlefield->level = 2;
	});
	campainMenu->buttons["Level3"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level3.txt");
		BH.battlefield->level = 3;
	});
	campainMenu->buttons["Level4"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level4.txt");
		BH.battlefield->level = 4;
	});
	campainMenu->buttons["Level5"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level5.txt");
		BH.battlefield->level = 5;
	});
	campainMenu->buttons["Level6"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level6.txt");
		BH.battlefield->level = 6;
	});

	campainMenu->buttons["Level7"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level7.txt");
		BH.battlefield->level = 7;
	});

	campainMenu->buttons["Level8"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level8.txt");
		BH.battlefield->level = 8;
	});

	campainMenu->buttons["Level9"]->addFuctionallity([=]() {
		BH.startBallte("res/Levels/Level9.txt");
		BH.battlefield->level = 9;
	});

	/*for (int i = 1; i <= 9; i++)
		if (i <= Config.availableLevels)
			campainMenu->buttons["Level" + std::to_string(i)]->block(false);
		else
			campainMenu->buttons["Level" + std::to_string(i)]->block(true);*/

	campainMenu->buttons["Back"] = std::make_shared<Button>(
		300, 680, 250, 50, this->font, "Back");

	campainMenu->buttons["Back"]->addFuctionallity([=]() {
		GH.popWindow(campainMenu);
		Config.load("res/config.txt");
	});

	for (auto button : campainMenu->buttons)
		campainMenu->interactiveElem.push_back(button.second);

	campainMenu->onActive = [=]() {

		std::fstream file;
		file.open("res/config.txt");
		Config.load(file, false);
		file.close();

		for (int i = 1; i <= 9; i++)
			if (i <= Config.availableLevels)
				campainMenu->buttons["Level" + std::to_string(i)]->block(false);
			else
				campainMenu->buttons["Level" + std::to_string(i)]->block(true);
	};

	GH.pushWindow(campainMenu);
}

void Game::editorState()
{
	auto battlefield = std::make_shared<Battlefield>(GameMode::Editor);
	battlefield->load("res/startMap.txt");
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
		//measureTime.restart();
		this->render();
		//std::cout << "Time Looptick render: " << measureTime.restart().asMilliseconds() <<std::endl;

	}
}
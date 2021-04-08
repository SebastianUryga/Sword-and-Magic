#include "pch.h"
#include "MainMenuState.h"


void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window->getSize()));
	this->backgroundTexture.loadFromFile("Textures\\background.jpg");
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initKeybinds()
{

	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE_BTN"] = new Button(300, 280, 250, 50,
		this->font, "New Game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
	this->buttons["SETTINGS_STATE_BTN"] = new Button(300, 380, 250, 50,
		this->font, "Settings",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
	this->buttons["EDITOR_STATE_BTN"] = new Button(300, 480, 250, 50,
		this->font, "EDITOR",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
	this->buttons["EXIT_GAME"] = new Button(300, 680, 250, 50,
		this->font, "Quit",
		sf::Color(100, 100, 100, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initBackground();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for(auto i : this->buttons)
		delete i.second;
}

// Functions

void MainMenuState::updateButtons()
{
	/* update all the buttons and hendles thier functionalaity*/
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// New Game 
	if (this->buttons["GAME_STATE_BTN"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	// Settings
	if (this->buttons["SETTINGS_STATE_BTN"]->isPressed())
	{
		this->states->push(new SettingState(this->stateData));
	}

	// Editor 
	if (this->buttons["EDITOR_STATE_BTN"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	// Quit the game
	if (this->buttons["EXIT_GAME"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::updateInput(const float & dt)
{
	
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions(nullptr);
	this->updateInput(dt);
	
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(background);

	this->renderButtons(target);
}

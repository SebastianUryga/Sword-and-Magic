#include "pch.h"
#include "SettingState.h"


void SettingState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window->getSize()));
	this->backgroundTexture.loadFromFile("Textures\\background.jpg");
	this->background.setTexture(&this->backgroundTexture);
}

void SettingState::initKeybinds()
{
}

void SettingState::initButtons()
{
	this->buttons["EXIT_GAME"] = new Button(600, 680, 250, 50,
		this->font, "Quit",
		sf::Color(100, 100, 100, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
}

SettingState::SettingState(StateData * state_data)
	: State(state_data)
{
	this->initBackground();
	this->initKeybinds();
	this->initButtons();
}


SettingState::~SettingState()
{
	for (auto i : this->buttons)
		delete i.second;
}

// Accesors

// Functions

void SettingState::updateButtons()
{
	/* update all the buttons and hendles thier functionalaity*/
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// Quit the game
	if (this->buttons["EXIT_GAME"]->isPressed())
	{
		this->endState();
	}
}

void SettingState::updateInput(const float & dt)
{

}

void SettingState::update(const float& dt)
{
	this->updateMousePositions(nullptr);
	this->updateInput(dt);

	this->updateButtons();
}

void SettingState::renderButtons(sf::RenderTarget* target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(background);

	this->renderButtons(target);
}

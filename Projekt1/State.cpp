#include "pch.h"
#include "State.h"

#define TILEWIDTH 32.f

State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->window = this->stateData->window;
	this->states = this->stateData->states;
	this->font = this->stateData->font;
	this->supportedKeys = this->stateData->supportedKeys;
	this->quit = false;
	this->keytime = 0.f;
	this->keytimeMax = 4.f;
}


State::~State()
{
}

const bool& State::getQuit() const
{
	return quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}


void State::endState()
{
	this->quit = true;
}

void State::OnMouseLeftButtonClick()
{
}

void State::OnMouseLeftButtonReleased()
{
}

void State::OnMouseRightButtonClick()
{
}

void State::updateMousePositions(sf::View *view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosTile =
		sf::Vector2i(
			(int)this->mousePosView.x / TILEWIDTH,
			(int)this->mousePosView.y / TILEWIDTH
		);
	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}

}

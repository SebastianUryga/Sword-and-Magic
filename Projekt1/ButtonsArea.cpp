#include "pch.h"
#include "ButtonsArea.h"


ButtonsArea::ButtonsArea() : BorderWindow(0,0,0,0)
{
	window = nullptr;
}


ButtonsArea::~ButtonsArea()
{
}

void ButtonsArea::setPos(float x, float y)
{
	//this->buttonEndTurn->setSize();
	//this->buttonSystem->setSize();
	this->background.setPosition(sf::Vector2f(x, y));
	this->buttonEndTurn->setPos(x + 50.f, y + 100.f);
	this->buttonSystem->setPos(x + 50.f, y + 200.f);
}

void ButtonsArea::move(float x, float y)
{
	this->background.move(x, y);
	this->buttonEndTurn->setPos(this->background.getPosition().x + 50.f, this->background.getPosition().y + 100.f);
	this->buttonSystem->setPos(this->background.getPosition().x + 50.f, this->background.getPosition().y + 200.f);
}

void ButtonsArea::initBackground()
{
	float posX = window->getView().getSize().x;
	this->background.setPosition(posX - 300.f, 0.f);
	this->background.setSize(sf::Vector2f(300.f, 300.f));
}

void ButtonsArea::initButtons()
{
	float posX = window->getView().getSize().x;
	buttonEndTurn = new Button(posX - 250, 100, 200, 50,
		&this->font, "End Turn",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
	buttonSystem = new Button(posX - 250, 150, 200, 50,
		&this->font, "System",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200));
}

void ButtonsArea::built(sf::Vector2f pos, sf::Font & font, sf::RenderWindow* window)
{
	this->font = font;
	this->window = window;
	initBackground();
	initButtons();
	offsetPosition = window->getView().getCenter();
}

void ButtonsArea::update(sf::Vector2i mousePosWindow)
{
	this->buttonEndTurn->update(mousePosWindow);
	this->buttonSystem->update(mousePosWindow);
	if (buttonEndTurn->isPressed())
		std::cout << "Next Turn" << std::endl;
	if (buttonSystem->isPressed())
		std::cout << "System dialog open" << std::endl;

	//update pos if scrold
	if (this->window->getView().getCenter() != offsetPosition)
	{
		offsetPosition = this->window->getView().getCenter();
		setPos(offsetPosition.x + window->getView().getSize().x, offsetPosition.y);
	}
}

void ButtonsArea::render(sf::RenderTarget * target)
{
	target->draw(this->background);
	buttonEndTurn->render(target);
	buttonSystem->render(target);
}

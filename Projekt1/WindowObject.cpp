#include "pch.h"
#include "GuiHandler.h"
//#include "WindowObject.h"

WindowObject::WindowObject(float x, float y, float width, float height, sf::Font& font)
{
	this->background.setSize(sf::Vector2f(width, height));
	this->background.setPosition(sf::Vector2f(x, y));
	this->background.setFillColor(sf::Color::Cyan);
	this->font = font;
}


WindowObject::~WindowObject()
{
	this->interactiveElem.clear();
}

void WindowObject::addText(std::string text, sf::Vector2f pos)
{
	pos += background.getPosition();
	texts.push_back(sf::Text(text, this->font, 20));
	texts.back().setPosition(pos);
}

void WindowObject::deactivate()
{
	this->active = false;
}

void WindowObject::activate()
{
	this->active = true;
}

void WindowObject::setPos(float x, float y)
{
	//do przetestowania
	float difX, difY;
	difX = x - this->background.getPosition().x;
	difY = y - this->background.getPosition().y;
	this->background.setPosition((int)x, (int)y);
	for (auto &btn : this->buttons)
		btn.second->move(difX, difY);
	for (auto &text : this->texts)
		text.move(difX,difY);
}

void WindowObject::close()
{
	if (GH.topWindow().get() != this)
		std::cout << "error: only top interface can be close" << std::endl;
	GH.popInt(GH.topWindow());
}

void WindowObject::update(const float dt, const sf::Vector2i mousePos)
{
	this->mousePos = mousePos;
	//update buttons
	for (auto &btn : this->buttons)
		btn.second->update(mousePos);
}

void WindowObject::render(sf::RenderTarget * target)
{
	target->draw(background);
	for (auto &text : this->texts)
		target->draw(text);
	for (auto &btn : this->buttons)
		btn.second->render(target);
}

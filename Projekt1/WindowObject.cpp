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
}

void WindowObject::deactivate()
{
}

void WindowObject::activate()
{
}

void WindowObject::close()
{
	if (GH.topInt().get() != this)
		std::cout << "error: only top interface can be close" << std::endl;
	GH.popInt(GH.topInt());
}

void WindowObject::OnMouseLeftButtonClick()
{
}

void WindowObject::update(const sf::Vector2i mousePos)
{
	this->mousePos = mousePos;
}

void WindowObject::render(sf::RenderTarget * target)
{
	target->draw(background);
}

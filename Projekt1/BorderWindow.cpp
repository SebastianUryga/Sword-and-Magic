#include "pch.h"
#include "BorderWindow.h"


BorderWindow::BorderWindow(float x, float y, float width, float height)
{
	background.setPosition(x, y);
	background.setSize(sf::Vector2f(width, height));
	background.setFillColor(sf::Color::Blue);
}


BorderWindow::~BorderWindow()
{
}

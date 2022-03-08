#include "WindowObject.h"

WindowObject::WindowObject(float x, float y, float width, float height, sf::Font& font)
{
	this->background.setSize(sf::Vector2f(width, height));
	this->background.setPosition(sf::Vector2f(x, y));
	this->background.setFillColor(sf::Color(100, 100, 100, 255));
	this->font = font;
}

WindowObject::~WindowObject()
{
	this->interactiveElem.clear();
}

bool WindowObject::contains(const sf::Vector2i& mousePos)
{
	return background.getGlobalBounds().contains((sf::Vector2f)mousePos);
}

void WindowObject::addText(std::string text, sf::Vector2f pos)
{
	pos += background.getPosition();
	auto sfText = std::make_shared<sf::Text>(text, this->font, 30);
	texts.push_back(sfText);
	texts.back()->setPosition(pos);
	texts.back()->setStyle(sf::Text::Italic);
}

void WindowObject::setPos(float x, float y)
{
	//do przetestowania
	float difX, difY;
	difX = x - this->background.getPosition().x;
	difY = y - this->background.getPosition().y;
	this->background.setPosition(x, y);
	for (auto& btn : this->buttons)
		btn.second->move(difX, difY);
	for (auto& text : this->texts)
		text->move(difX, difY);
}

void WindowObject::deactivate()
{
	this->active = false;
}

void WindowObject::activate()
{
	this->active = true;
	this->onActive();
}

void WindowObject::close()
{
	if (GH.topWindow().get() != this)
		std::cout << "error: only top interface can be close" << std::endl;
	GH.popWindow(GH.topWindow());
}

void WindowObject::update([[maybe_unused]] const float dt)
{
	//update buttons
	for (auto& btn : this->buttons)
		btn.second->update();
}

void WindowObject::render(sf::RenderTarget* target)
{
	target->draw(background);
	for (auto& text : this->texts)
		target->draw(*text);
	for (auto& btn : this->buttons)
		btn.second->render(target);
}

bool PopupWindow::contains(sf::Vector2f mousePos)
{
	return true;
}

void PopupWindow::clickRight(bool down, [[maybe_unused]] bool previousState)
{
	if (down == false)
		GH.closePopup();
}

PopupWindow::PopupWindow()
{
	this->iner = nullptr;
}

PopupWindow::~PopupWindow()
{
}
#include "pch.h"
#include "GuiHandler.h"
//#include "HeroWindow.h"

void HeroWindow::initBackground()
{

}

void HeroWindow::initButtons()
{
	
	buttons["Quit"] = std::make_shared<Button>(
		this->background.getPosition().x + 700,
		this->background.getPosition().y + 750,
		50, 30, &this->font, "OK",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200)
		);
	
	buttons["Dismis"] = std::make_shared <Button>(
		this->background.getPosition().x + 600,
		this->background.getPosition().y + 600,
		50, 30, &this->font, "Dismis",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200)
		);
}

HeroWindow::HeroWindow(const HeroInstance * hero)
	:WindowObject(400,400,800,800, GH.globalFont)
{
	this->curHero = hero;
	this->initButtons();
	portraitImage.setPosition(0, 0);
	//portraitImage.setTexture()
}


HeroWindow::~HeroWindow()
{
}

void HeroWindow::updateButtons(const sf::Vector2i mousePos)
{
	for (auto btn : this->buttons)
	{
		btn.second->update(mousePos);
	}
}

void HeroWindow::update(const sf::Vector2i mousePos)
{
	WindowObject::update(mousePos);

}

void HeroWindow::render(sf::RenderTarget * target)
{
	WindowObject::render(target);
}

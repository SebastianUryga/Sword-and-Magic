#include "pch.h"
#include "GuiHandler.h"
//#include "HeroWindow.h"

void HeroWindow::initGarrison(std::vector<Troop>& troops)
{
	this->gar = std::make_shared<GarrnisonInterface>(
			troops, this->background.getPosition() + sf::Vector2f(30, 400));
	for (auto slot : gar->slots)
	{
		this->texts.push_back(slot->number);
		this->interactiveElem.push_back(slot);
	}
}

void HeroWindow::initBackground()
{

}

void HeroWindow::initButtons()
{
	this->buttons["Quit"] = std::make_shared<Button>(
		this->background.getPosition().x + 700,
		this->background.getPosition().y + 450,
		50, 30, &this->font, "OK",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200)
		);
	this->buttons["Quit"]->addFuctionallity([=]() {this->close(); });
	this->buttons["Dismis"] = std::make_shared <Button>(
		this->background.getPosition().x + 600,
		this->background.getPosition().y + 300,
		50, 30, &this->font, "Dismis",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200)
		);
	this->buttons["Dismis"]->addFuctionallity([=]() {this->dismissCurrent(); });
	this->interactiveElem.push_back(this->buttons["Quit"]);
	this->interactiveElem.push_back(this->buttons["Dismis"]);
}

HeroWindow::HeroWindow(HeroInstance * hero)
	:WindowObject(200,100,800,500, GH.globalFont)
{
	this->curHero = hero;
	this->initGarrison(hero->troops);
	this->initButtons();
	this->addText(hero->subTypeName, sf::Vector2f(50, 5));
	this->portraitImage.setPosition(this->background.getPosition()+sf::Vector2f(5,5));
	this->portraitImage.setTexture(*graphics.allHeroesPortraits);
	this->portraitImage.setTextureRect(Graphics::selectPortriat(hero->name));
	
}


HeroWindow::~HeroWindow()
{
}

void HeroWindow::dismissCurrent()
{
	std::function<void()> onYes = [=]() {PI->dismissHero(this->curHero); close(); };
	PI->showYesNoDialog("czy na pewno chcesz\n zwolnic bohatera?", onYes, [=]() {});
}

void HeroWindow::setPos(float x, float y)
{
	WindowObject::setPos(x, y);
	this->portraitImage.setPosition(x, y);
}

void HeroWindow::update(const float dt, const sf::Vector2i mousePos)
{
	WindowObject::update(dt,mousePos);

}

void HeroWindow::render(sf::RenderTarget * target)
{
	WindowObject::render(target);
	target->draw(portraitImage);
	this->gar->render(target);
}

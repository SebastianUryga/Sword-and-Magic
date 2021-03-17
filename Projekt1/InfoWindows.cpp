#include "pch.h"
#include "InfoWindows.h"
#include "GuiHandler.h"

void PopupWindow::clickRight(bool down, bool previousState)
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

TavernWindow::TavernWindow(int player, const MP2::ObjectInstance* obj)
	: WindowObject(500, 400, 500, 300, GH.globalFont), selected(0), tavern(obj)
{

	this->buttons["Recruit"] = std::make_shared<Button>(
		this->background.getPosition().x + 150,
		this->background.getPosition().y + 200,
		100, 30, &this->font, "Recruit",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200)
		);

	if (!PI->canRecruitHero(player, obj))
		this->buttons["Recruit"]->block(true);

	this->buttons["Recruit"]->addFuctionallity([=]() {
		auto h = heroPortraits[this->selected]->h;
		h->setOwner(player);
		h->setTilePos(obj->getVisitablePos());
		world.addMapObject(h);
		this->close();
	});// mozna nowa funcja zrobic w PI recruitHero(tavern,hero)

	this->buttons["Quit"] = std::make_shared<Button>(
		this->background.getPosition().x + 50,
		this->background.getPosition().y + 200,
		100, 30, &this->font, "Quit",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(0, 0, 20, 200)
		);
	this->buttons["Quit"]->addFuctionallity([=]() {this->close(); });

	this->heroPortraits[0] = std::make_shared<HeroPortrait>(
		selected, 0,
		this->background.getPosition().x + 50,
		this->background.getPosition().y + 100,
		PI->getTavernHero(PI->currentColorTurn)
		);
	this->heroPortraits[1] = std::make_shared<HeroPortrait>(
		selected, 1,
		this->background.getPosition().x + 120,
		this->background.getPosition().y + 100,
		PI->getTavernHero(PI->currentColorTurn)
		);
	this->addText("Znajdujesz sie w tawernie,\n mozesz tu rekrutowac nowych bohaterow",
		sf::Vector2f(30,30));
	this->interactiveElem.push_back(buttons["Recruit"]);
	this->interactiveElem.push_back(buttons["Quit"]);
	this->interactiveElem.push_back(this->heroPortraits[0]);
	this->interactiveElem.push_back(this->heroPortraits[1]);
}

void TavernWindow::render(sf::RenderTarget * target)
{
	WindowObject::render(target);
	target->draw(heroPortraits[0]->portriat);
	target->draw(heroPortraits[1]->portriat);
	if (this->selected)
		target->draw(this->heroPortraits[1]->selectFrame);
	else
		target->draw(this->heroPortraits[0]->selectFrame);
}

void TavernWindow::HeroPortrait::clickLeft(bool down, bool previousState)
{
	if(down && previousState == false)
		*this->sel = id;
}

void TavernWindow::HeroPortrait::clickRight(bool down, bool previousState)
{
	if(down)
		GH.makePopup(std::make_shared<HeroWindow>(this->h));
}

TavernWindow::HeroPortrait::HeroPortrait(int& sel, int id, int x, int y, HeroInstance * H)
	:h(H),sel(&sel)
{
	this->id = id;
	this->shape = sf::FloatRect((float)x, (float)y, 50, 60);
	this->selectFrame = sf::RectangleShape(sf::Vector2f(50,60));
	this->selectFrame.setOutlineThickness(2);
	this->selectFrame.setOutlineColor(sf::Color::Yellow);
	this->selectFrame.setPosition(x, y);
	this->selectFrame.setFillColor(sf::Color::Transparent);
	this->portriat.setTexture(*graphics.allHeroesPortraits);
	this->portriat.setTextureRect(Graphics::selectPortriat(h->name));
	this->portriat.setPosition(sf::Vector2f((float)x,(float)y));
}

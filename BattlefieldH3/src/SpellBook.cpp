#include "GuiHandler.h"

SpellBook::SpellBook(Spell& selectedSpell, int actualMana)
	:WindowObject(400,200,700,400,GH.globalFont), spellToCast(selectedSpell)
{
	for (size_t i = 0; i < allSpells.size(); i++)
	{
		auto pos = this->background.getPosition();
		pos += sf::Vector2f{ 20.f + (i % 7) * 90,10.f + (i / 7) * 70 };
		auto temp = std::make_shared<SpellIcon>(*this, pos, allSpells[i]);
		this->spellIcons.push_back(temp);
		this->interactiveElem.push_back(this->spellIcons.back());
	}

	this->manaQuantityText = std::make_shared<sf::Text>("Mana: "+ std::to_string(actualMana), this->font, 20);
	this->manaQuantityText->setPosition(400 + 10, 200 + 360);
	this->texts.push_back(manaQuantityText);

	this->buttons["OK"] = std::make_shared<Button>(
		400+620, 200+350, 60, 30, &this->font, "OK"
		);
	this->buttons["OK"]->addFuctionallity([=]() {
		close();
	});
	this->interactiveElem.push_back(buttons["OK"]);
}

SpellBook::~SpellBook() {}

void SpellBook::render(sf::RenderTarget* target)
{
	WindowObject::render(target);
	for (auto item : this->spellIcons)
	{
		item->render(target);
	}
}

void SpellIcon::clickLeft(bool down, bool previousState)
{
	if (down == false && previousState)
	{
		owner.spellToCast = this->type;
		owner.close();
	}
}

void SpellIcon::clickRight(bool down, bool previousState)
{
	if (down  && previousState == false)
	{
		auto pop = std::make_shared<WindowObject>(
			GH.mousePosWindow.x, GH.mousePosWindow.y,150,100,GH.globalFont);
		pop->background.setFillColor(sf::Color(120, 120, 100, 255));
		auto t = sf::Text(spellToString[this->type.spell], GH.globalFont, 20);
		auto size = sf::Vector2f(t.getGlobalBounds().width, t.getGlobalBounds().height);

		pop->addText(spellToString[this->type.spell], sf::Vector2f((150 - size.x)/2, 20));
		GH.makePopup(pop);
	}
}

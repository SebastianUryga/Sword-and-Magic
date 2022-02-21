#pragma once
#include "WindowObject.h"
#include "Player.h"
#include "Graphics2.h"
#include "Spell.h"
class WindowObject;
class SpellBook;
class Graphics2;
class Spell;

class SpellIcon : public InterfaceElem
{
private:
	sf::Sprite sprite;
	SpellBook& owner;
	void clickLeft(bool down, bool previousState) override;
	void clickRight(bool down, bool previousState) override;

public:
	SpellIcon(SpellBook& book, const sf::Vector2f pos, Spell type) :
		owner(book),
		type(type)
	{
		this->shape = sf::FloatRect(pos, { 74, 74 });
		this->sprite.setTexture(*graphics2.allSpellIcons);
		this->sprite.setTextureRect(Graphics2::selectSpellIcon(type));
		this->sprite.setPosition(pos);
	}
	void render(sf::RenderTarget* target)
	{
		target->draw(sprite);
	}
	Spell type;
};

class SpellBook :
	public WindowObject
{
public:
	SpellBook(Spell& selectedSpell, Player& player);
	~SpellBook();
	Spell& spellToCast;
	Player& player;
	std::list<std::shared_ptr<SpellIcon>> spellIcons;
	std::shared_ptr<sf::Text> manaQuantityText;

	void render(sf::RenderTarget* target) override;
};

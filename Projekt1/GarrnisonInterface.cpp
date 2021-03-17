#include "pch.h"
#include "GarrnisonInterface.h"
#include "interface_gamearea.h"

GarrnisonSlot * GarrnisonInterface::getSelected()
{
	return this->selected;
}

void GarrnisonInterface::selectSlot(GarrnisonSlot * slot)
{
	selected = slot;
}

GarrnisonInterface::GarrnisonInterface(std::vector<Troop>& garrnison, sf::Vector2f pos)
	:garrnison(garrnison)
{
	this->selected = nullptr;
	this->slots.resize(7);
	for (int i = 0; i < 7; ++i)
	{
		this->slots[i] = std::make_shared<GarrnisonSlot>(
			this, i, (i*62)+pos.x, pos.y);

		this->slots[i]->setTroop(&garrnison[i]);
	}
	
}


GarrnisonInterface::~GarrnisonInterface()
{
}

void GarrnisonInterface::render(sf::RenderTarget * target)
{
	for (auto& slot : this->slots)
	{
		
		target->draw(slot->sprite);
		if (slot->stack->monster == Monster::NO_CREATURE)
			continue;
		target->draw(slot->number);
	}
	if (this->selected)
		target->draw(this->selected->selectFrame);
		
}

void GarrnisonInterface::updateSlots()
{
	for (auto& slot : this->slots)
	{
		slot->setTroop(&garrnison[slot->id]);
	}
}

void GarrnisonSlot::setPos(sf::Vector2f pos)
{
	this->shape = sf::FloatRect(pos.x, pos.y, 58, 64);
	this->sprite.setPosition(pos);
	this->number.setPosition(pos + sf::Vector2f(2, 48));
	this->selectFrame.setPosition(pos);
}

void GarrnisonSlot::setTroop(Troop* troop)
{
	stack = troop;
	this->sprite.setTextureRect(Graphics::selectPortrait(troop->monster));
	std::string count = std::to_string(troop->count);
	this->number.setString(count);
}

void GarrnisonSlot::clickLeft(bool down, bool previousState)
{
	if (down && previousState == false)
	{
		if (owner->getSelected())
		{

			if (this == owner->getSelected())
			{
				// open creature window 
				
				owner->selectSlot(nullptr);
			}
			else
			{
				if (stack->monster == owner->selected->stack->monster)
				{
					PI->mergeStacks(owner->garrnison, owner->selected->id, this->id);
					owner->updateSlots();
					owner->selectSlot(nullptr);
				}
				else
				{
					PI->swapStacks(owner->garrnison, owner->selected->id, this->id);
					owner->updateSlots();
					owner->selectSlot(nullptr);
				}
			}
		}
		else if (!(stack->monster == Monster::NO_CREATURE))
			owner->selectSlot(this);
	}
}

void GarrnisonSlot::clickRight(bool down, bool previousState)
{
}

GarrnisonSlot::GarrnisonSlot(GarrnisonInterface* owner, int id, float x, float y )
	: owner(owner), id(id)
{
	this->selectFrame = sf::RectangleShape(sf::Vector2f(58, 64));
	this->selectFrame.setOutlineThickness(3);
	this->selectFrame.setOutlineColor(sf::Color::Yellow);
	this->selectFrame.setFillColor(sf::Color::Transparent);
	this->sprite.setTexture(*graphics.allCreaturePortraits);
	this->number.setFont(GH.globalFont);
	this->number.setCharacterSize(15);
	this->setPos(sf::Vector2f(x, y));
}
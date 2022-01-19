#include "GuiHandler.h"

GarrnisonSlot* Garrnison::getSelected()
{
	return this->selected;
}

void Garrnison::selectSlot(GarrnisonSlot* slot)
{
	selected = slot;
}

void Garrnison::mergeStacks(int stack1Id, int stack2Id) // Mergeing to stack1
{
	this->garrnison[stack1Id].count += this->garrnison[stack2Id].count;
	this->garrnison[stack2Id].monster = Monster::NO_CREATURE;
	this->garrnison[stack2Id].count = 0;
}

void Garrnison::swapStacks(int stack1Id, int stack2Id)
{
	std::swap(this->garrnison[stack1Id], this->garrnison[stack2Id]);
}

Garrnison::Garrnison(std::vector<Troop>& garrnison, sf::Vector2f pos) :
	garrnison(garrnison)
{
	this->background.setSize(sf::Vector2f(74*7,80));
	this->background.setPosition(pos);
	this->background.move(-10, -10);
	this->background.setFillColor(sf::Color(120, 110, 120, 255));
	this->selected = nullptr;
	this->slots.resize(7);
	for (int i = 0; i < 7; ++i)
	{
		this->slots[i] = std::make_shared<GarrnisonSlot>(
			this, i, (i * 74) + pos.x, pos.y);

		this->slots[i]->setTroop(&garrnison[i]);
	}
}

Garrnison::~Garrnison()
{
}

void Garrnison::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	for (auto& slot : this->slots)
	{
		target->draw(slot->sprite);
		if (slot->stack->monster == Monster::NO_CREATURE)
			continue;
		target->draw(*slot->number);
	}
	if (this->selected)
		target->draw(this->selected->selectFrame);
}

void Garrnison::updateSlots()
{
	for (auto& slot : this->slots)
	{
		slot->setTroop(&garrnison[slot->id]);
	}
}

void GarrnisonSlot::setPos(sf::Vector2f pos)
{
	this->shape = sf::FloatRect(pos.x, pos.y, 70, 67);
	this->sprite.setPosition(pos);
	this->number->setPosition(pos + sf::Vector2f(2, 48));
	this->selectFrame.setPosition(pos);
}

void GarrnisonSlot::setTroop(Troop* troop)
{
	this->stack = troop;
	this->sprite.setTexture(*graphics2.creaturesTextures[troop->monster].portrait);
	//this->sprite.setTextureRect(Graphics::selectPortrait(troop->monster));
	std::string count = std::to_string(troop->count);
	this->number->setString(count);
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
				GH.pushWindowT<SelectionWindow>(*owner->selected->stack);
				owner->updateSlots();
				owner->selectSlot(nullptr);
			}
			else
			{
				if (this->stack->monster == owner->selected->stack->monster)
				{
					owner->mergeStacks(owner->selected->id, this->id);
					owner->updateSlots();
					owner->selectSlot(nullptr);
				}
				else
				{
					owner->swapStacks(owner->selected->id, this->id);
					owner->updateSlots();
					owner->selectSlot(nullptr);
				}
			}
		}
		else
		{
			if (this->stack->monster == Monster::NO_CREATURE)
				GH.pushWindowT<SelectionWindow>(*this->stack);
			else
				owner->selectSlot(this);
		}
	}
}
void GarrnisonSlot::clickRight([[maybe_unused]] bool down, [[maybe_unused]] bool previousState)
{
}
GarrnisonSlot::GarrnisonSlot(Garrnison* owner, int id, float x, float y) :
	id(id),
	owner(owner)
{
	this->selectFrame = sf::RectangleShape(sf::Vector2f(60, 64));
	this->selectFrame.setOutlineThickness(3);
	this->selectFrame.setOutlineColor(sf::Color::Yellow);
	this->selectFrame.setFillColor(sf::Color::Transparent);
	//this->sprite.setTexture(*graphics.allCreaturePortraits);
	this->number = std::make_shared < sf::Text>();
	this->number->setFont(GH.globalFont);
	this->number->setCharacterSize(15);
	this->setPos(sf::Vector2f(x, y));
}
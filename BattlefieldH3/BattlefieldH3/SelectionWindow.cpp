#include "GuiHandler.h"

SelectionWindow::SelectionWindow(Troop& troop)
	: WindowObject(400,200,600,500,GH.globalFont), troopToEdit(troop)
{
	if (troopToEdit.monster == Monster::NO_CREATURE)
		this->troopQuantity = 0;
	else
		this->troopQuantity = troop.count;
	this->selectedCreature = troopToEdit.monster;
	this->addText(std::to_string(this->troopQuantity), { 300,450 });
	this->creaturePortraits.resize(allMonseters.size());
	sf::Vector2f pos;
	// setting position of creature portrets
	for (int i = 0 ; i < allMonseters.size() ; i++)
	{
		pos = this->background.getPosition() + sf::Vector2f(30, 30);
		pos += sf::Vector2f((64 * i) % 512, std::floor((64 * i) / 512)*64);
		this->creaturePortraits[i] = std::make_shared<ClickablePortrait>(allMonseters[i]);
		this->creaturePortraits[i]->sprite.setPosition(pos);
		this->creaturePortraits[i]->shape = sf::FloatRect(pos.x,pos.y,50,50);
		this->creaturePortraits[i]->onClick = [=](){
			selectedCreature = allMonseters[i];
		};
		this->interactiveElem.push_back(this->creaturePortraits[i]);
	}


	this->incrementingBtn = std::make_shared<Button>(
		100, 450, 100, 30, &this->font, "+");
	this->incrementingBtn->move(
		this->background.getPosition().x,
		this->background.getPosition().y);

	if (this->troopQuantity > 40) this->incrementingBtn->block(true);

	this->decrementingBtn = std::make_shared<Button>(
		350, 450, 100, 30, &this->font, "-");
	this->decrementingBtn->move(
		this->background.getPosition().x,
		this->background.getPosition().y);

	if (this->troopQuantity < 1) this->decrementingBtn->block(true);

	this->decrementingBtn->addFuctionallity([=]()
	{
		troopQuantity--;
		if (troopQuantity < 1) decrementingBtn->block(true);
		incrementingBtn->block(false);
		texts.back().setString(std::to_string(troopQuantity));
	});
	this->buttons["-"] = this->decrementingBtn;

	this->incrementingBtn->addFuctionallity([=]()
	{
		troopQuantity++;
		if (troopQuantity > 40) incrementingBtn->block(true);
		decrementingBtn->block(false);
		texts.back().setString(std::to_string(troopQuantity));
	});
	this->buttons["+"] = this->incrementingBtn;

	this->buttons["OK"] = std::make_shared<Button>(
		930, 650, 60, 30, &this->font, "OK"
		);
	this->buttons["OK"]->addFuctionallity([=]() { 
		troopToEdit.monster = selectedCreature;
		troopToEdit.count = troopQuantity;
		close(); 
	});
	this->interactiveElem.push_back(this->buttons["OK"]);
	this->interactiveElem.push_back(this->buttons["+"]);
	this->interactiveElem.push_back(this->buttons["-"]);
}

void SelectionWindow::render(sf::RenderTarget* target)
{
	WindowObject::render(target);

	static sf::RectangleShape selectingFrame(sf::Vector2f(58, 64));
	selectingFrame.setOutlineThickness(1);
	selectingFrame.setOutlineColor(sf::Color::Yellow);
	selectingFrame.setFillColor(sf::Color::Transparent);
	for (auto portrait : this->creaturePortraits)
	{
		target->draw(portrait->sprite);
		if (portrait->id == selectedCreature)
		{
			selectingFrame.setPosition(portrait->sprite.getPosition());
			target->draw(selectingFrame);
		}
	}
	
	
}

void SelectionWindow::ClickablePortrait::clickLeft(bool down, bool priviesState)
{
	if (down)
	{
		// play sound
	}
	else if (priviesState && (down == false))
	{
		this->onClick();
	}
}

#include "pch.h"
#include "GuiHandler.h"

GuiHandler & GH = GuiHandler::Get();

void GuiHandler::pushInt(std::shared_ptr<WindowObject> newInt)
{
	assert(newInt);
	if (std::find(listInt.begin(), listInt.end(), newInt) != listInt.end())
		assert(0); // do not add same object twice
	
	if (!listInt.empty())
		listInt.front()->deactivate();
	listInt.push_front(newInt);
	
	newInt->activate();
}

void GuiHandler::popInt(std::shared_ptr<WindowObject> top)
{
	assert(this->listInt.front() == top);
	this->listInt.pop_front();
	if (!this->listInt.empty())
		this->listInt.front()->activate();
}

std::shared_ptr<WindowObject> GuiHandler::topInt()
{
	if (listInt.empty())
		return std::shared_ptr<WindowObject>();
	else
		return listInt.front();
}

bool GuiHandler::empty()
{
	return this->listInt.empty();
}

GuiHandler::~GuiHandler()
{
}

GuiHandler & GuiHandler::Get()
{
	static GuiHandler GH;
	return GH;
}

void GuiHandler::update(const sf::Vector2i mousePos)
{

}

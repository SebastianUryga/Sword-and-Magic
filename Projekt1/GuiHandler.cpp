#include "pch.h"
#include "GuiHandler.h"

GuiHandler & GH = GuiHandler::Get();

void GuiHandler::handleMouseButtonClick(sf::Mouse::Button btn, bool isPressed)
{
	if (!this->topInt())
		return;
	auto hlp = this->topInt()->interactiveElem;
	for (auto & i : hlp)
	{
		auto prev = i->mouseState(btn);
		if (!isPressed)
			i->updateMouseState(btn, isPressed);

		if (i->contains(this->mousePosWindow))
		{
			if (isPressed)
				i->updateMouseState(btn, isPressed);
			switch (btn)
			{
			case sf::Mouse::Left:
				i->clickLeft(isPressed,prev);
				break;
			case sf::Mouse::Right:
				i->clickRight(isPressed, prev);
				break;
			default:
				break;
			}
		}
			
	}
}

void GuiHandler::pushInt(std::shared_ptr<WindowObject> newInt)
{
	assert(newInt);
	if (std::find(winodwList.begin(), winodwList.end(), newInt) != winodwList.end())
		assert(0); // do not add same object twice
	
	if (!winodwList.empty())
		winodwList.front()->deactivate();
	winodwList.push_front(newInt);
	
	newInt->activate();
}

void GuiHandler::popInt(std::shared_ptr<WindowObject> top)
{
	assert(this->winodwList.front() == top);
	this->winodwList.pop_front();
	if (!this->winodwList.empty())
		this->winodwList.front()->activate();
}

std::shared_ptr<WindowObject> GuiHandler::topInt()
{
	if (winodwList.empty())
		return std::shared_ptr<WindowObject>();
	else
		return winodwList.front();
}

bool GuiHandler::empty()
{
	return this->winodwList.empty();
}

GuiHandler::~GuiHandler()
{
}

void GuiHandler::handleEvents(std::stack<State*>& states,sf::RenderWindow* window, sf::Event& event)
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			
		}

		if (event.type == sf::Event::MouseMoved)
		{
			this->handleMouseMotion();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				handleMouseButtonClick(sf::Mouse::Left, true);
				states.top()->OnMouseLeftButtonClick();
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				handleMouseButtonClick(sf::Mouse::Right, true);
				states.top()->OnMouseRightButtonClick();
			}

		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			handleMouseButtonClick(sf::Mouse::Left, false);
			states.top()->OnMouseLeftButtonReleased();

			handleMouseButtonClick(sf::Mouse::Right, false);

		}

		this->mousePosWindow = (sf::Vector2f)sf::Mouse::getPosition(*window);
	}
}

void GuiHandler::handleMouseMotion()
{
	if (this->empty())
		return;
	auto hlp = this->topInt()->interactiveElem;
	for (auto & i : hlp)
	{
		if (i->contains(mousePosWindow))
		{
			i->hover(true);
		}
		else
			i->hover(false);
	}
}

GuiHandler & GuiHandler::Get()
{
	static GuiHandler GH;
	return GH;
}

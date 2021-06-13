#include "pch.h"
#include "GuiHandler.h"

GuiHandler& GH = GuiHandler::Get();

void GuiHandler::pushWindow(std::shared_ptr<WindowObject> newInt)
{
	assert(newInt);
	if (std::find(vecWindow.begin(), vecWindow.end(), newInt) != vecWindow.end())
		assert(0); // do not add same object twice

	if (!vecWindow.empty())
		vecWindow.back()->deactivate();
	vecWindow.push_back(newInt);

	newInt->activate();
}

void GuiHandler::makePopup(std::shared_ptr<WindowObject> w)
{
	if (popupWindow)
		popupWindow->iner = w;
	else
	{
		popupWindow = std::make_shared<PopupWindow>();
		popupWindow->iner = w;
	}
}

void GuiHandler::closePopup()
{
	this->popupWindow->iner = nullptr;
}

void GuiHandler::popWindow(std::shared_ptr<WindowObject> top)
{
	assert(this->vecWindow.back() == top);
	this->vecWindow.pop_back();
	if (!this->vecWindow.empty())
		this->vecWindow.back()->activate();
}

std::shared_ptr<WindowObject> GuiHandler::topWindow()
{
	if (vecWindow.empty())
		return std::shared_ptr<WindowObject>();
	else
		return vecWindow.back();
}

bool GuiHandler::empty()
{
	return this->vecWindow.empty();
}

GuiHandler::~GuiHandler()
{
}

void GuiHandler::handleMouseMotion()
{
	if (this->empty())
		return;

	auto hlp = this->topWindow()->interactiveElem;
	if (popupWindow && popupWindow->iner) hlp.push_back(popupWindow);
	for (auto& i : hlp)
	{
		if (i->contains(mousePosWindow))
		{
			i->hover(true);
		}
		else
			i->hover(false);
	}
}

void GuiHandler::handleMouseButtonClick(sf::Mouse::Button btn, bool isPressed)
{
	if (!this->topWindow())
		return;
	auto hlp = this->topWindow()->interactiveElem;
	if (popupWindow && popupWindow->iner) hlp.push_back(popupWindow);
	for (auto& i : hlp)
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
				i->clickLeft(isPressed, prev);
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

GuiHandler& GuiHandler::Get()
{
	static GuiHandler GH;
	return GH;
}

void GuiHandler::update(const float& dt)
{
	if(!GH.empty())
		this->topWindow()->update(dt);
}

void GuiHandler::render(sf::RenderTarget* target)
{
	for (auto it : this->vecWindow)
		it->render(target);
	if (popupWindow && popupWindow->iner)
		popupWindow->iner->render(target);
}

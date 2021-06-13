#include "pch.h"
#include "GuiHandler.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, sf::Color idleColor,
	sf::Color hoverColor, sf::Color activeColor, sf::Color blockColor)
{
	this->buttonState = Button_states::BTN_IDLE;

	this->shape = sf::FloatRect(x, y, width, height);
	this->background.setPosition(sf::Vector2f(x, y));
	this->background.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(22);
	this->text.setPosition(
		this->background.getPosition().x + (this->background.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->background.getPosition().y + (this->background.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->activeColor = activeColor;
	this->hoverColor = hoverColor;
	this->idleColor = idleColor;
	this->blockColor = blockColor;

	this->background.setFillColor(this->idleColor);
}

Button::~Button()
{
}


//Accesor
const bool Button::isPressed() const
{
	return buttonState == Button_states::BTN_PRESSED;
}

bool Button::isBlocked()
{
	return this->buttonState == Button_states::BTN_BLOCK;
}

void Button::clickRight(bool pressed, bool previousState)
{
	if (pressed && popupWindow)
		GH.makePopup(popupWindow);
}

void Button::clickLeft(bool pressed, bool previousState)
{
	if (isBlocked())
		return;
	if (pressed)
	{
		// play sound
	}
	else if (previousState && (pressed == false))
	{
		this->onButtonClicked();
	}
}

void Button::hover(bool on)
{
	if (!isBlocked())
	{
		if (on)
			this->buttonState = Button_states::BTN_HOVER;
		else
			this->buttonState = Button_states::BTN_IDLE;
	}
}

void Button::addFuctionallity(const std::function<void()>& f)
{
	this->onClick = f;
}

void Button::addRightClickPopup(const std::shared_ptr<WindowObject> window)
{
	this->popupWindow = window;
}

void Button::block(bool on)
{
	if (on)
		this->buttonState = Button_states::BTN_BLOCK;
	else
		this->buttonState = Button_states::BTN_IDLE;
}

void Button::onButtonClicked()
{
	this->onClick();
}

void Button::setPos(float x, float y)
{
	this->shape.left = x;
	this->shape.top = y;
	this->background.setPosition(sf::Vector2f(x, y));
	this->text.setPosition(
		this->background.getPosition().x + (this->background.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->background.getPosition().y + (this->background.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}

void Button::setText(std::string t)
{
	this->text.setString(t);
}

void Button::move(float x, float y)
{
	this->background.move(x, y);
	this->text.move(x, y);
	this->shape.top += y;
	this->shape.left += x;
}

void Button::update()
{
	switch (buttonState)
	{
	case Button_states::BTN_HOVER:
		this->background.setFillColor(this->hoverColor);
		break;
	case Button_states::BTN_IDLE:
		this->background.setFillColor(this->idleColor);
		break;
	case Button_states::BTN_PRESSED:
		this->background.setFillColor(this->activeColor);
		break;
	case Button_states::BTN_BLOCK:
		this->background.setFillColor(this->blockColor);
		break;
	default:
		this->background.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->text);
}
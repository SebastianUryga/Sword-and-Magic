#include "pch.h"
#include "Button.h"


Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;
	
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

	this->background.setFillColor(this->idleColor);
}


Button::~Button()
{
}


//Accesor
const bool Button::isPressed() const
{
	return buttonState == BTN_PRESSED;
}

bool Button::isBlocked()
{
	return this->buttonState == BTN_BLOCK;
}

void Button::clickRight(bool pressed, bool previousState)
{
	//some popup in future
}

void Button::clickLeft(bool pressed, bool previousState)
{
	if(isBlocked())
		return;
	std::cout << previousState << " " << pressed << std::endl;
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
			this->buttonState = BTN_HOVER;
		else
			this->buttonState = BTN_IDLE;
	}
}


void Button::addFuctionallity(const std::function<void()>& f)
{
	this->onClick = f;
}

void Button::block(bool on)
{
	if (on)
		this->buttonState = BTN_BLOCK;
	else
		this->buttonState = BTN_IDLE;
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

void Button::move(float x, float y)
{
	this->background.move(x, y);
	this->text.move(x, y);
	this->shape.top += y;
	this->shape.left += x;
}

//Functions
void Button::update(const sf::Vector2i mousePos)
{
	//*Update the booleans for hover and pressed*/
	this->buttonState = BTN_IDLE;

	//hover
	if (this->background.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		this->buttonState = BTN_HOVER;

		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_PRESSED;
		}
	}
	
	switch (buttonState)
	{
	case BTN_HOVER:
		this->background.setFillColor(this->hoverColor);
		break;
	case BTN_IDLE:
		this->background.setFillColor(this->idleColor);
		break;
	case BTN_PRESSED:
		this->background.setFillColor(this->activeColor);
		break;
	default:
		this->background.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget * target)
{
	target->draw(this->background);
	target->draw(this->text);	
}

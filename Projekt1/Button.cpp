#include "pch.h"
#include "Button.h"


Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;
	
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(22);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->activeColor = activeColor;
	this->hoverColor = hoverColor;
	this->idleColor = idleColor;

	this->shape.setFillColor(this->idleColor);
}


Button::~Button()
{
}


//Accesor
const bool Button::isPressed() const
{
	return buttonState == BTN_PRESSED;
}	

void Button::setPos(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);
}

//Functions
void Button::update(const sf::Vector2i mousePos)
{
	//*Update the booleans for hover and pressed*/
	this->buttonState = BTN_IDLE;

	//hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
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
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);	
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);	
}

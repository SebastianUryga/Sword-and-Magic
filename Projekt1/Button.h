#pragma once

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};
class Button
{
private:
	unsigned short buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, 
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	//Accesor
	const bool isPressed() const;

	//functions
	void setPos(float x, float y);
	void update(const sf::Vector2i mousePos);
	void render(sf::RenderTarget* target);
	
};


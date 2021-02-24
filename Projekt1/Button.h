#pragma once
#include"IntObject.h"

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED, BTN_BLOCK};
class Button : public IntObject
{
private:

	button_states buttonState;

	sf::RectangleShape background;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	std::function<void()> onClick;
public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, 
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	//Accesor
	const bool isPressed() const;
	bool isBlocked();

	void clickRight(bool down, bool previousState) override;
	void clickLeft(bool down, bool previousState) override;
	void hover(bool on) override;

	//functions
	void addFuctionallity(const std::function<void()>& f);
	void block(bool on);
	void onButtonClicked();
	void setPos(float x, float y);
	void move(float x, float y);
	void update(const sf::Vector2i mousePos);
	void render(sf::RenderTarget* target);
	
};


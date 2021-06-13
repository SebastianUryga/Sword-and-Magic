#pragma once
#include "InterfaceElem.h"

class WindowObject;

enum class Button_states { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED, BTN_BLOCK };

class Button : public InterfaceElem
{
private:

	Button_states buttonState;

	sf::RectangleShape background;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
	sf::Color blockColor;

	std::function<void()> onClick;
	std::shared_ptr<WindowObject> popupWindow;
public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor = sf::Color(70, 70, 70, 200),
		sf::Color hoverColor = sf::Color(150, 150, 150, 200),
		sf::Color activeColor = sf::Color(0, 0, 20, 200),
		sf::Color blockColor = sf::Color(200, 200, 200, 200));
	virtual ~Button();

	//Accesor
	const bool isPressed() const;
	bool isBlocked();

	void clickRight(bool down, bool previousState) override;
	void clickLeft(bool down, bool previousState) override;
	void hover(bool on) override;

	//functions
	void addFuctionallity(const std::function<void()>& f);
	void addRightClickPopup(const std::shared_ptr<WindowObject> window);
	void block(bool on);
	void onButtonClicked();
	void setPos(float x, float y);
	void setText(std::string t);
	void move(float x, float y);
	void update();
	void render(sf::RenderTarget* target);

};
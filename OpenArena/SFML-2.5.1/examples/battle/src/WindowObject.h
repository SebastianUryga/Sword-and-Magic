#pragma once
#include "Button.h"
class WindowObject
{
public:
	sf::RectangleShape background;

	std::vector<std::shared_ptr<InterfaceElem>> interactiveElem;
	std::map<std::string, std::shared_ptr<Button>> buttons;
	std::vector<sf::Text> texts;

	bool active;
	sf::Font font;

	WindowObject(float x, float y, float width, float height, sf::Font& font);
	virtual ~WindowObject();

	bool contains(const sf::Vector2i& mousePos);
	void addText(std::string text, sf::Vector2f pos);
	void setPos(float x, float y);
	void deactivate();
	virtual void activate();
	virtual void close();

	virtual void update(const float dt);
	virtual void render(sf::RenderTarget* target);
};

class PopupWindow : public InterfaceElem
{
public:
	std::shared_ptr<WindowObject> iner;

	template <typename T, typename... Args>
	void setWindow(Args&&... args)
	{
		this->iner = std::make_shared<T>(std::forward<Args>(args)...);
	}

	bool contains([[maybe_unused]] sf::Vector2f mousePos) override
	{
		return true;
	}
	void clickRight(bool down, bool previousState) override;
	PopupWindow();
	virtual ~PopupWindow();
};

#pragma once
#include "Game.h"
class GuiHandler
{
private:

	std::vector<std::shared_ptr<WindowObject>> vecWindow;
	std::shared_ptr<PopupWindow> popupWindow;
public:

	void pushWindow(std::shared_ptr<WindowObject> newInt); //deactivate old top interface, activates this one and pushes to the top
	template <typename T, typename ... Args>
	void pushWindowT(Args && ... args)
	{
		auto newInt = std::make_shared<T>(std::forward<Args>(args)...);
		pushWindow(newInt);
	}
	void makePopup(std::shared_ptr<WindowObject> w);
	void closePopup();
	void popWindow(std::shared_ptr<WindowObject> top);
	std::shared_ptr<WindowObject> topWindow(); //returns top Window
	bool empty();

	sf::Font globalFont;
	sf::Vector2f mousePosWindow;

	GuiHandler() {}
	virtual ~GuiHandler();

	void handleMouseMotion();
	void handleMouseButtonClick(sf::Mouse::Button btn, bool isPressed);
	static GuiHandler& Get();

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

extern GuiHandler& GH;
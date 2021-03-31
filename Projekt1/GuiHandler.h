#pragma once
#include "State.h"
#include "HeroWindow.h"
#include "TownWindow.h"
#include "interface_gamearea.h"
namespace Interface
{
	class GameArea;
};
class GuiHandler
{
private:

	sf::Vector2f mousePosWindow;
	std::vector<std::shared_ptr<WindowObject>> vecWindow;
	std::shared_ptr<PopupWindow> popupWindow;
	void handleMouseButtonClick(sf::Mouse::Button btn, bool isPressed);
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

	GuiHandler() {}
	virtual ~GuiHandler();

	void handleEvents(std::stack<State*>& states,sf::RenderWindow* window, sf::Event& event);
	void handleMouseMotion();
	void renderAll(sf::RenderTarget * target);
	static GuiHandler &	Get();
};

extern GuiHandler& GH;
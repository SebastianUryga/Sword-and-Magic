#pragma once
#include "State.h"
#include "HeroWindow.h"
#include "interface_gamearea.h"
namespace Interface
{
	class GameArea;
};
class GuiHandler
{
private:

	sf::Vector2f mousePosWindow;
	std::list<std::shared_ptr<WindowObject>> winodwList;
	std::shared_ptr<PopupWindow> popupWindow;
	void handleMouseButtonClick(sf::Mouse::Button btn, bool isPressed);
public:

	void pushInt(std::shared_ptr<WindowObject> newInt); //deactivate old top interface, activates this one and pushes to the top
	template <typename T, typename ... Args>
	void pushIntT(Args && ... args)
	{
		auto newInt = std::make_shared<T>(std::forward<Args>(args)...);
		pushInt(newInt);
	}
	void makePopup(std::shared_ptr<WindowObject> w);
	void closePopup();
	void popInt(std::shared_ptr<WindowObject> top);

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
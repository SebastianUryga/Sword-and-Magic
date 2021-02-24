#pragma once
#include "HeroWindow.h"
#include "GameState.h"
namespace Interface
{
	class GameArea;
};
class GuiHandler
{
private:

	std::list<std::shared_ptr<WindowObject>> listInt;
	
public:

	void pushInt(std::shared_ptr<WindowObject> newInt); //deactivate old top interface, activates this one and pushes to the top
	template <typename T, typename ... Args>
	void pushIntT(Args && ... args)
	{
		auto newInt = std::make_shared<T>(std::forward<Args>(args)...);
		pushInt(newInt);
	}
	void popInt(std::shared_ptr<WindowObject> top);

	std::shared_ptr<WindowObject> topInt(); //returns top interface
	bool empty();

	sf::Font globalFont;

	GuiHandler() {}
	virtual ~GuiHandler();

	static GuiHandler &	Get();

	void update(const sf::Vector2i mousePos);
};

extern GuiHandler& GH;
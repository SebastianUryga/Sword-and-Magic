#pragma once
#include"WindowObject.h"

class HeroInstance;
class WindowObject;
class GuiHandler;
namespace MP2{
	class ObjectInstance;
}

class PopupWindow : public IntObject
{
public:
	
	std::shared_ptr<WindowObject> iner;

	template <typename T,typename ... Args>
	void setWindow(Args && ... args)
	{
		iner = std::make_shared<T>(args);
	}

	bool contains(sf::Vector2f mousePos) override { return true; }
	void clickRight(bool down, bool previousState) override;
	PopupWindow();
	virtual ~PopupWindow();
};

class TavernWindow : public WindowObject
{
public:
	class HeroPortrait : public IntObject
	{
	public:
		std::string hoverName;
		HeroInstance * h;

		void clickLeft(bool down, bool previousState) override;
		void clickRight(bool down, bool previousState) override;
		HeroPortrait(int& sel, int id, float x, float y, HeroInstance * H);

		sf::RectangleShape selectFrame;
		sf::Sprite portriat;

		int* sel; // nie wiem czy to potrzebne
		int id;
	};
	std::shared_ptr<HeroPortrait> heroPortraits[2];
	int selected; // 0 -> left, 1 -> right, 2 -> no one
	const MP2::ObjectInstance * tavern;
	TavernWindow(int player, const MP2::ObjectInstance* obj);
	void render(sf::RenderTarget * target) override;
};
#pragma once
#include "ButtonsArea.h"
#include "Graphics.h"
#include "GuiHandler.h"

class HeroInstance;
struct Path;
struct Arrow;
namespace MP2
{
	class ObjectInstance;
}
namespace Interface
{
	class AdvMapArrows;
	enum { GameMode, EditorMode };
	class GameArea
	{
	private:

		int mode;
		sf::IntRect rectMaps;
		
		sf::RenderWindow* window;

		sf::Vector2i scrollOffset;
		float scrollSpeed;
		float scrollTime;

		void setTexturesToAllSprites();

	public:
		
		MP2::ObjectInstance* selection;
		HeroInstance* curHero() const;
		// const TownInstance * curTown() const;

		sf::Vector2i getScrollOffset();
		bool needScroll(); 
		bool contains(sf::Vector2i point);

		void built(sf::RenderWindow* window, int mode);

		GameArea();
		virtual ~GameArea();

		void updateInput(const float dt, sf::Vector2i mousePosWindow);
		void update(const float dt, sf::Vector2i mousePosWindow, int color);
		void render(sf::RenderTarget * target, int color);
	};
	void MouseCursorAreaClickLeft(const sf::Vector2i mousePos);
	void MouseCursorAreaPressRight();

	void ShowPathOrStartMoveHero(); // Hero*
	GameArea & GetGameArea();
	ButtonsArea & GetButtonsArea();
	int startGame();
	int HumanTurn();
	static GameArea gameArea;
	static ButtonsArea buttonsArea;


	class AdvMapArrows : public std::vector<Arrow>
	{
	private:
		std::shared_ptr<Path> path;
		int topIndex;
	public:
		Arrow& top();
		void calcuateArrows(std::shared_ptr<Path> path);
		AdvMapArrows();
		void eraseArrow(const sf::Vector2i& heroPos);

	};
	AdvMapArrows & GetHeroMoveArrows();
	static AdvMapArrows heroMoveArrows;
	
	/*class CAdvMapInt 
	{
	private:
		MP2::ObjectInstance* selection;
		void fmoveHero();
		void fshowSpellbok();
		void fadventureOPtions();
		void fsystemOptions();
		void fnextHero();
		void fendTurn();
	public:
		void tileLClicked(const sf::Vector2i &mapPos);

		const HeroInstance * curHero() const;
	};*/
}
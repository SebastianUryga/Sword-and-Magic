#pragma once
#include "MapObject.h"
#include "ButtonsArea.h"
#include "Graphics.h"
#include "Tiles.h"
#include "PlayerInterface.h"

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
	class GameArea : public WindowObject
	{
	private:

		int mode;
		sf::IntRect rectMaps;
		
		sf::View view;
		sf::RenderWindow* window;

		/// Where to scroll, example (0,0) means dont need to scroll
		sf::Vector2f scrollDirection;
		/// View position divide by Tile Width
		sf::Vector2f scrollOffset;
		float scrollSpeed;
		float scrollTime;

		void setTexturesToAllSprites();
		
	public:
		void initView();
		MP2::ObjectInstance* selection;
		HeroInstance* curHero() const;
		// const TownInstance * curTown() const;

		sf::Vector2f getScrollOffset() const;
		sf::Vector2f getScrollDirection() const;
		void focusOn(sf::Vector2f pos);
		bool needScroll();
		bool contains(sf::Vector2i point);

		void built(sf::RenderWindow* window, int mode);

		GameArea();
		virtual ~GameArea();
		void updateView();
		void updateInput(const float dt, sf::Vector2i mousePosWindow);
		void update(const float dt, sf::Vector2i mousePosWindow);
		void render(sf::RenderTarget * target) override;
	};
	void MouseCursorAreaClickLeft(const sf::Vector2i mousePos);
	void MouseCursorAreaPressRight();

	GameArea & GetGameArea();
	ButtonsArea & GetButtonsArea();
	
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
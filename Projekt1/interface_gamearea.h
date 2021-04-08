#pragma once
#include "MapObject.h"
#include "ButtonsArea.h"
#include "TownInstance.h"
#include "BattleHandler.h"
#include "Tiles.h"
#include "PlayerInterface.h"
#include "InfoWindows.h"
#include "color.h"
#include "Direction.h"
#include "Graphics.h"
class HeroInstance;
class TownInstance;
struct Path;
struct Arrow;

namespace MP2
{
	class ObjectInstance;
}

namespace Interface
{
	class AdvMapArrows;
	class HeroList;
	enum { GameMode, EditorMode };
	class GameArea : public WindowObject
	{
	private:

		int mode;
		sf::IntRect rectMaps;
		
		sf::View* view;
		sf::RenderWindow* window;

		/// Where to scroll, example (0,0) means dont need to scroll
		sf::Vector2f scrollDirection;
		/// View position divide by Tile Width
		sf::Vector2f scrollOffset;
		float scrollSpeed;
		float scrollTime;
		
	public:
		void initView();
		void initHeroList();
		MP2::ObjectInstance* selection;
		HeroInstance* curHero() const;
		TownInstance* curTown() const;
		HeroList* playerListOfHero;
		// const TownInstance * curTown() const;

		//Accesors
		sf::Vector2f getScrollOffset() const;
		sf::Vector2f getScrollDirection() const;
		sf::Vector2i getScrollTileOffset() const;
		sf::View* getView() const;
		int getMode() const;
		bool contains(sf::Vector2i point) const;

		void focusOn(sf::Vector2f pos);
		bool needScroll();
		void built(sf::RenderWindow* window, int mode);

		GameArea();
		virtual ~GameArea();
		void updateView();
		void updateInput(const float dt, sf::Vector2i mousePosWindow);
		void update(const float dt, sf::Vector2i mousePosWindow);
		void render(sf::RenderTarget * target) override;
	};
	void MouseCursorAreaClickLeft(const sf::Vector2i mousePos);
	void MouseCursorAreaClickRight(const sf::Vector2i mousePos);

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
	
	class HeroList
	{
	public:
		class HeroItem : public IntObject
		{
		public:
			HeroInstance* h;
			sf::Sprite heroPortrait;
			sf::RectangleShape selectFrame;
			sf::RectangleShape movment;
			void clickLeft(bool down, bool previousState) override;
			HeroItem(int id,int* selected, float x, float y, HeroInstance * h);
			int id;
		private:
			int * sel;
		};
		sf::RectangleShape background;
		std::vector<HeroItem*> portraits;
		HeroList(float x, float y);
		int selected;
		void addHero(HeroInstance* h);
		void setHeroes(std::vector<HeroInstance*> &playerHeroes);
		void update();
		void render(sf::RenderTarget* target);
		
	};
	class TownList
	{
	public:
		class TownItem : public IntObject
		{
		public:
			TownInstance* t;
			sf::Sprite sprite;
			sf::RectangleShape selectFrame;
			void clickLeft(bool down, bool previousState) override;
			TownItem(int id, int* selected, float x, float y, TownInstance* t);
		private:
			int *sel;
		};
		sf::RectangleShape background;
		std::vector<TownItem*> twons;
		TownList(float x, float y);
		int selected;
		void addTown(TownInstance* t);
	};
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
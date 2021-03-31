#pragma once
#include "GuiHandler.h"

class HeroInstance;
class TownInstance;
class WindowObject;
class HeroWindow;
class TownWindow;
class Button;
class GuiHandler;
namespace Interface
{
	class GameArea;
}


class PlayerInterface
{
public:
	//Variables
	sf::Clock globalClock; // reset in game class
	bool end;
	bool canCalcuatePaths;
	std::shared_ptr<Interface::GameArea> gameArea;
	std::vector < const HeroInstance*> playerHeroes;
	int currentColorTurn;

	PlayerInterface();
	virtual ~PlayerInterface();

	int getCurrentColor();
	void select(MP2::ObjectInstance *sel, bool centerView = true);
	void selectionChanged();
	void focusOn(sf::Vector2f on);
	void focusOn(sf::Vector2i on, bool fade = false);
	void focusOn(const MP2::ObjectInstance *obj, bool fade = false);
	void calcuatePaths();
	void mergeStacks(std::vector<Troop>& garr, int stack1Id, int stack2Id);
	void swapStacks(std::vector<Troop>& garr, int stack1Id, int stack2Id);
	void stopMovement(const HeroInstance * hero);
	void tileLClicked(const sf::Vector2i mapPos);
	void tileRClicked(const sf::Vector2i mapPos);
	void dismissHero(HeroInstance * hero);
	void openHeroWindow(HeroInstance * hero); //shows hero window with given hero
	void openTownWindow(TownInstance* town);
	void openWindow(int player, const MP2::ObjectInstance* tav);
	bool canRecruitHero(int player, const MP2::ObjectInstance * obj);
	HeroInstance* getTavernHero(int player);

	void bulid(BuildingID building, int slot);
	//void initMovement(const TryMoveHero &details, const HeroInstance * ho, const int3 &hp);//initializing objects and performing first step of move
	//void heroVisit(const HeroInstance * visitor, const ObjectInstance * visitedObj, bool start);
	//void heroVisitsTown(const HeroInstance* hero, const TownInstance * town);
	void nextPlayer();
	void tileLClickedEditor(const sf::Vector2i mapPos); // name function to change
	void showYesNoDialog(const std::string &text, std::function<void()> onYes, std::function<void()> onNo);
private:
};

extern PlayerInterface * PI;
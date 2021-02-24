#pragma once
#include "GuiHandler.h"

class HeroInstance;
class WindowObject;
class HeroWindow;
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
	std::shared_ptr<Interface::GameArea> gameArea;
	int currentColorTurn;

	PlayerInterface();
	virtual ~PlayerInterface();

	int getCurrentColor();
	void select(const MP2::ObjectInstance *sel, bool centerView = true);
	void selectionChanged();
	void focusOn(sf::Vector2f on);
	void focusOn(sf::Vector2i on, bool fade = false);
	void focusOn(const MP2::ObjectInstance *obj, bool fade = false);
	Path *getAndVerifyPath(const HeroInstance * h);
	void stopMovement(const HeroInstance * hero);
	void tileLClicked(const sf::Vector2i mapPos);
	void tileRClicked(const sf::Vector2i mapPos);
	void dismissHero(const HeroInstance * hero);
	void openHeroWindow(const HeroInstance * hero); //shows hero window with given hero
	//void initMovement(const TryMoveHero &details, const HeroInstance * ho, const int3 &hp);//initializing objects and performing first step of move
	//void heroVisit(const HeroInstance * visitor, const ObjectInstance * visitedObj, bool start);
	//void heroVisitsTown(const HeroInstance* hero, const TownInstance * town);
	void showYesNoDialog(const std::string &text, std::function<void()> onYes, std::function<void()> onNo);
private:
};

extern PlayerInterface * PI;
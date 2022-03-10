#pragma once
#include "WindowObject.h"
#include "Garrnison.h"
#include "SelectionWindow.h"
#include "SpellBook.h"
#include "Player.h"
#include "BattleUnit.h"

class BattleHandler;
class Button;
class WindowObject;
class BattleUnit;
struct BattleObstacle;
class BattleHandler;
class Garrnison;
class Spell;
class Player;

extern BattleHandler BH;

struct BattleTile
{
	sf::Vector2i pos;
	sf::RectangleShape shape;
	BattleUnit* unit;
	bool blocked;
	std::list<std::shared_ptr<BattleObstacle>> obstacles;
};

enum class GameMode
{
	Editor,
	Game
};

class Battlefield :
	public WindowObject,
	public InterfaceElem
{
private:
	sf::Sprite backgroud;
	Background backgroundType;
	GameMode mode;

	std::vector<std::vector<BattleTile>> tiles;
	std::vector<std::shared_ptr<BattleObstacle>> obstacles;
	std::set<BattleUnit*> selectedUnits;

	std::vector<Troop> army[2];
	std::vector<std::shared_ptr<Player>> players;

	// interface using only in Editing mode
	std::shared_ptr<Garrnison> gar1;
	std::shared_ptr<Garrnison> gar2;

	void initArmy();
	void initPlayers();
	void initPlayersArmy2();
	void initButtons();
	void initTileMap();
	void initMovmentMarker();
	void sortUnits();

	Monster selectedUnitType;
	Spell spellToCast;
	sf::Sprite activeSpellIcon;
	sf::RectangleShape selectingArea;
	std::shared_ptr<sf::Text> cooldownNumber;

	float markerVisableTimeLeft = 0.f;
	sf::CircleShape movmentMarker;
	void putMovmentMarker(const sf::Vector2i& pos, bool attck);
	void setBackground(Background background);
public:
	bool gamePaused = true;
	int level = -1;
	std::vector<std::shared_ptr<BattleUnit>> units;

	bool containsIsBattlefield(sf::Vector2i pos) const;
	std::shared_ptr<BattleUnit> getUnit(sf::Vector2i pos) const;
	sf::Vector2i getSize() const;
	BattleTile& getTile(sf::Vector2i pos);
	BattleTile& getTile(int x, int y);
	bool isTileBlocked(const sf::Vector2i pos) const;
	bool areUnitSelected() const;
	const BattleTile& getTile(const sf::Vector2i pos) const;
	void changeUnitPos(BattleUnit* unit, sf::Vector2i oldPos, sf::Vector2i newPos);
	bool addUnit(std::shared_ptr<BattleUnit> unit, sf::Vector2i pos, bool enemy);
	void addObsticle(BattleObstacle::Type type, sf::Vector2i pos);
	void removeUnit(std::shared_ptr<BattleUnit> unit);
	void removeObsticle(std::shared_ptr<BattleObstacle> obs);

	void close() override;

	virtual void keyPressed([[maybe_unused]] const sf::Keyboard& key) override;

	virtual void activate() override;
	virtual void clickLeft(bool down, bool previousState) override;
	virtual void clickRight(bool down, bool previousState) override;
	virtual void hover(bool on) override;

	Battlefield(GameMode mode);
	virtual ~Battlefield();

	void updateMovmentMarker(const float dt);
	void update(const float dt) override;
	void render(sf::RenderTarget* target) override;

	void save(const std::string& path);
	bool load(const std::string& path);
	friend class BattleHandler;
};

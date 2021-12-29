#pragma once
#include "BattleUnit.h"
#include "Garrnison.h"
#include "SelectionWindow.h"
#include "SpellBook.h"
#include "WindowObject.h"
#include "Player.h"

class BattleUnit;

#define BATTLE_OFFSET_X 2
#define BATTLE_OFFSET_Y 3

#define B_TILE_WIDTH 60.f
#define B_TILE_HEIGHT 60.f
#define BATTLEFIELD_WIDHT 24
#define BATTLEFIELD_HEIGHT 12

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
	GameMode mode;

	std::vector<std::vector<BattleTile>> tiles;
	std::vector<std::shared_ptr<BattleUnit>> units;
	std::vector<std::shared_ptr<BattleObstacle>> obstacles;
	std::set<BattleUnit*> selectedUnits;

	std::vector<Troop> army[2];
	std::vector<std::shared_ptr<Player>> players;

	// interface using only in Editing mode
	std::shared_ptr<Garrnison> gar1;
	std::shared_ptr<Garrnison> gar2;

	void initArmy();
	void initPlayers();
	void initArmy2();
	void initButtons();
	void initStartUnits();
	void initMovmentMarker();
	void sortUnits();

	bool gamePaused = false;
	Monster selectedUnitType;
	Spell spellToCast;
	sf::RectangleShape selectingArea;
	std::shared_ptr<sf::Text> cooldownNumber;

	float markerVisableTimeLeft = 0.f;
	sf::CircleShape movmentMarker;
	void putMovmentMarker(const sf::Vector2i& pos, bool attck);

public:
	bool containsIsBattlefield(sf::Vector2i pos) const;
	std::shared_ptr<BattleUnit> getUnit(sf::Vector2i pos) const;
	sf::Vector2i getSize() const;
	BattleTile& getTile(sf::Vector2i pos);
	BattleTile& getTile(int x, int y);
	bool isTileBlocked(const sf::Vector2i pos) const;
	const BattleTile& getTile(const sf::Vector2i pos) const;
	void changeUnitPos(BattleUnit* unit, sf::Vector2i oldPos, sf::Vector2i newPos);
	void addUnit(std::shared_ptr<BattleUnit> unit, sf::Vector2i pos, bool enemy);
	void addObsticle(BattleObstacle::Type type, sf::Vector2i pos);
	void removeUnit(std::shared_ptr<BattleUnit> unit);
	void removeObsticle(std::shared_ptr<BattleObstacle> obs);

	void close() override;

	virtual void keyPressed([[maybe_unused]] const sf::Keyboard& key)
	{}

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

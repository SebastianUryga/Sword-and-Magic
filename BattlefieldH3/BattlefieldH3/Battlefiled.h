#pragma once
#include "BattleUnit.h"
#include "WindowObject.h"
#include "Garrnison.h"

class BattleUnit;

#define B_TILE_WIDTH 50.f
#define B_TILE_HEIGHT 50.f
#define BATTLEFIELD_WIDHT  26
#define BATTLEFIELD_HEIGHT  12


struct BattleTile
{

    sf::Vector2i pos;
    sf::RectangleShape shape;
    BattleUnit* unit;
    bool blocked;

};

enum class GameMode {Editor, Game};

class Battlefield :
    public WindowObject, public InterfaceElem
{
private:
    sf::Sprite backgroud;
    GameMode mode;

    std::vector<std::vector<BattleTile>> tiles;
    std::vector<std::shared_ptr<BattleUnit>> units;
    std::vector<std::shared_ptr<BattleObstacle>> obstacles;
    std::set <BattleUnit*> selectedUnits;

    std::vector<Troop> army[2];

    // interface using only in Editing mode
    std::shared_ptr<Garrnison> gar1;
    std::shared_ptr<Garrnison> gar2;

    void initArmy();
    void initButtons();
    void initStartUnits();
    void sortUnits();

    Monster selectedUnitType;
    sf::RectangleShape selectingArea;
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

    virtual void keyPressed(const sf::Keyboard& key) {}

    virtual void clickLeft(bool down, bool previousState) override;
    virtual void clickRight(bool down, bool previousState) override;
    virtual void hover(bool on) override;

    Battlefield(GameMode mode);
    virtual ~Battlefield();

    void update(const float dt) override;
    void render(sf::RenderTarget* target) override;

    void save(const std::string& path);
    bool load(const std::string& path);
    friend class BattleHandler;
};


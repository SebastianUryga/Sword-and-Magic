#pragma once
#include "WindowObject.h"
#include "BattleUnit.h"

class BattleUnit;

#define BTILEWIDTH 50.f
#define BTILEHEIGHT 50.f
#define BATTLEFIELDWIDHT  26
#define BATTLEFIELDHEIGHT  13

struct BattleTile
{

    sf::Vector2i pos;
    sf::RectangleShape shape;
    BattleUnit* unit;
    bool blocked;

};

class Battlefield :
    public WindowObject
{
private:
    sf::Sprite backgroud;

    std::vector<std::vector<BattleTile>> tiles;
    std::vector<std::shared_ptr<BattleUnit>> units;
    void initButtons();
    void sortUnits();
public:
    bool containsIsBattlefield(sf::Vector2i pos);
    std::shared_ptr<BattleUnit> getUnit(sf::Vector2i pos);
    void changeUnitPos(BattleUnit* unit, sf::Vector2i oldPos, sf::Vector2i newPos);
    void addUnit(std::shared_ptr<BattleUnit> unit, sf::Vector2i pos,bool enemy);

    void close() override;

    Battlefield();
    virtual ~Battlefield();

    void update(const float dt, const sf::Vector2i mousePos) override;
    void render(sf::RenderTarget* target) override;

    friend class BattleHandler;
};


#pragma once
#include "AnimationComponent.h"
#include "BattlePathFinder.h"
#include "Graphics.h"
#include "GameConstants.h"

class Missle;

template<typename T>
struct VectorCompare
{
    bool operator() (const sf::Vector2<T>& a, const sf::Vector2<T>& b) const
    {
        if (a.y < b.y)  return true;
        if (a.y > b.y)  return false;
        return (a.x < b.x);
    }
};
typedef std::set<sf::Vector2i, VectorCompare<int>> TileSet;

enum class AnimationState
{
    ATTACKING, BLOCKING, RECIVING_DMG, SHOOTHING, MOVING, START_MOVING, END_MOVEING, DIEING, IDLE
};
enum class Order
{
    AGRESIVE_POSITION, DEFENSIVE_POS, MOVE, ATTACK
};
class BattleUnit :
    public InterfaceElem
{
private:
    sf::Sprite sprite;
    sf::Vector2i pos;
    sf::Vector2i pos2;
    sf::Vector2f velocity;
    sf::Vector2f offset;
    float speed;
    int maxHp;
    int hp;
    int arrows;
    int damage;
    int attack;
    int defence;
    Monster type;
    bool alive;
    bool enemy;
    bool bigCreature;
    bool shouter;
    AnimationState animationState;
    Order order;
    bool moving;
    bool moving2;
    bool attacking;
    bool attacked;
    bool shooing;
    bool shooted;
    bool reverseAttaking;
    bool recivingDamage;
    bool lastDirection; // false - left, true - right
    std::shared_ptr <Battle::PathFinder> pathfinder;
    TileSet neighbourTilePos;
    std::shared_ptr<Missle> missle;
    sf::RectangleShape lineHP;
    BattleUnit* target;
    sf::Text text;
    sf::Vector2i destenation;
    float attackCoulddown;
    float actualAttackCoulddown;
    AnimationComponent* animation;
    void initAnimation();
    void initStatistic();

public:
    bool isShouter() const;
    bool isBig() const;
    TileSet& getNeighbourTilePos();
    sf::Vector2i getPos() const;
    sf::Vector2i getPos2() const;
    BattleUnit* getTarget() const;
    bool getAttacked();
    bool getShooted();
    bool getAlive() const;
    Monster getType() const;
    bool isEnemy() const;
    bool haveDefensePosition() const;

    void idle();
    void doMove(sf::Vector2f diraction);
    bool makeAttack(sf::Vector2i target);
    bool makeShot(sf::Vector2i target);
    void reciveDamage(sf::Vector2i from);
    void makeBlock(sf::Vector2i from);
    void dieing();
    void turn();

    void fixSpritePos();
    bool giveDestenation(sf::Vector2i des);
    bool choseTarget(BattleUnit* t);
    void setPathfinder(Battlefield* field);
    void setPos(sf::Vector2i pos);
    void setVelocity(sf::Vector2f direction);
    void setEnemy(bool enemy);
    void giveOrder(Order order);

    void clickLeft(bool down, bool previousState) override;

    BattleUnit(Monster type);
    virtual ~BattleUnit();

    void updateNeighbourPos();
    void updateAnimation(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);

    friend class BattleHandler;
};

class Missle
{
public:
    Missle(BattleUnit* unit);
    ~Missle();
    sf::Sprite sprite;
    sf::RectangleShape shape;
    float speed;
    const sf::Vector2i startingPos;
    sf::Vector2f velocity;
    sf::Vector2f position;

    void setTarget(sf::Vector2i targetPos);
    sf::Vector2i getTilePos() const;

    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
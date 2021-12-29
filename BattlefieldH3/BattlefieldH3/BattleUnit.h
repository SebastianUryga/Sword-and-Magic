#pragma once
#include "AnimationComponent.h"
#include "Animator.h"
#include "BattlePathFinder.h"
#include "GameConstants.h"
#include "Graphics.h"
#include "Graphics2.h"
#include "Configuration.h"


class InterfaceElem;
class Missle;

template <typename T>
struct VectorCompare
{
	bool operator()(const sf::Vector2<T>& a, const sf::Vector2<T>& b) const
	{
		if (a.y < b.y)
			return true;
		if (a.y > b.y)
			return false;
		return (a.x < b.x);
	}
};
typedef std::set<sf::Vector2i, VectorCompare<int>> TileSet;

enum class AnimationState
{
	ATTACKING,
	BLOCKING,
	RECIVING_DMG,
	SHOOTHING,
	MOVING,
	START_MOVING,
	END_MOVEING,
	DIEING,
	RUNNING,
	IDLE
};
enum class Order
{
	AGRESIVE_STANCE,
	DEFENSIVE_POS,
	MOVE,
	ATTACK
};

struct CastedSpell
{
	float timeRemain;
	Spell type;
	CastedSpell(Spell s, float t = 0) :
		timeRemain(t),
		type(s)
	{}
	bool operator==(const CastedSpell& s)
	{
		return type == s.type;
	}
};

class BattleUnit :
	public InterfaceElem
{
private:
	Monster type;
	sf::Vector2f velocity;
	sf::Vector2i pos;
	sf::Vector2i pos2;
	sf::Vector2f offset;
	float speed;
	int maxHp;
	int hp;
	int arrows;
	int damage;
	int attack;
	int defence;
	bool alive;
	bool enemy;
	bool bigCreature;
	bool shooter;
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
	std::shared_ptr<Battle::PathFinder> pathfinder;
	float timeToUpdatePathfinder;
	TileSet neighbourTilePos;
	struct DamageText
	{
		sf::Text number;
		float displayTimeRemain;
	};
	std::list<DamageText> damageTexts;
	std::list<CastedSpell> castedSpellList;
	std::shared_ptr<Missle> missle;
	sf::RectangleShape lineHP;
	BattleUnit* target;
	sf::Text text;
	sf::Vector2i destenation;
	float attackCoulddown;
	float actualAttackCoulddown;
	Spell spellToAnimate;
	sf::Sprite sprite;
	sf::Sprite spellEffect;
	std::shared_ptr<Animator> animator;
	bool isBlid = false;
	AnimationComponent* animation;
	AnimationComponent* spellEffectAnimation;
	void initAnimation();
	void initAnimation2();
	void initStatistic();
	void initTextDmg(const int dmg);

public:
	bool moveMakeColision(const sf::Vector2i& moveDirection, const std::shared_ptr<Battlefield> battlefield) const;
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
	bool isEnemyWith(const BattleUnit* unit) const;
	bool haveDefensePosition() const;

	void idle();
	void doMove(sf::Vector2i diraction);
	bool makeAttack(const sf::Vector2i target);
	bool makeShot(const sf::Vector2i target);
	void reciveDamage(const sf::Vector2i from, const int dmg);
	void makeBlock(const sf::Vector2i from, const int dmg);
	void dieing();
	void turn();

	void fixSpritePos();
	bool giveDestenation(sf::Vector2i des);
	bool choseTarget(BattleUnit* t);
	void setPathfinder(Battlefield* field);
	void setPos(sf::Vector2i pos);
	void setVelocity(const sf::Vector2i direction);
	void setEnemy(bool enemy);
	void giveOrder(Order order);

	void clickLeft(bool down, bool previousState) override;

	BattleUnit(Monster type);
	virtual ~BattleUnit();

	void updatePathfinder(const float& dt);
	void updateNeighbourPos();
	void updateAnimation(const float& dt);
	void updateAnimation2(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	friend class BattleHandler;
	friend class Spell;
};

class Missle
{
public:
	Missle(BattleUnit* unit);
	~Missle();
	float speed;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	const sf::Vector2i startingPos;
	sf::Vector2f velocity;
	sf::Vector2f position;

	void setTarget(sf::Vector2i targetPos);
	sf::Vector2i getTilePos() const;

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};
#pragma once
#include "Battlefiled.h"

class Monster;
class Battlefield;
class Spell;
class InterfaceElem;
class Battlefield;
class BattleUnit;
class Player;

class BattleHandler
{
public:
	BattleHandler();
	virtual ~BattleHandler();

	std::shared_ptr<Battlefield> battlefield;
	bool battleBegan = false;
	void startBallte(std::string path);

	void spellCasted(Spell spell, Player* player);

	sf::Vector2i choseMoveDirection(BattleUnit* unit) const;
	bool nextToEachOther(BattleUnit* u1, BattleUnit* u2);
	BattleUnit* findNeerestEnemy(BattleUnit* unit);
	BattleUnit* calculateBestTargetFor(BattleUnit* unit);
	void makeDecision(BattleUnit* unit);
	void unitAttakced(BattleUnit* unit);
	void unitMadeShot(BattleUnit* unit);
	void unitKilled(BattleUnit* unit);
	void updateMissle(BattleUnit* unit);
	void update(const float& dt);
private:
	void handleAggressiveStance(BattleUnit* unit);
	void handleDefenceStance(BattleUnit* unit);
	void handleAttackOrder(BattleUnit* unit);
	void handleMoveOrder(BattleUnit* unit);
	double length(sf::Vector2i vec) const;
	int calculateDamage(BattleUnit* unit, BattleUnit* target, bool attackBlocked);
	std::queue<Monster> armyQueque[2];
	int nuberUnitsInBattle[2];
	void initArmyQueque();
	void updateQueque();
};

extern BattleHandler BH;

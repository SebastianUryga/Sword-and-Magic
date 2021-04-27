#pragma once
#include "Battlefield.h"

class Battlefield;
class BattleUnit;

class BattleHandler
{
public:
	BattleHandler();
	virtual ~BattleHandler();

	std::shared_ptr<Battlefield> battlefield;
	void startBallte();

	sf::Vector2i choseMoveDirection(BattleUnit* unit) const;
	bool nextToEachOther(BattleUnit* u1, BattleUnit* u2);
	BattleUnit* findNeerestEnemy(BattleUnit* unit);
	void makeDecision(BattleUnit* unit);
	void unitAttakced(BattleUnit* unit);
	void unitMadeShot(BattleUnit* unit);
	void unitDied(BattleUnit* unit);
	void updateMissle(BattleUnit* unit);
	void update(const float& dt);
private:
	int calculateDamage(BattleUnit* unit, BattleUnit* target);
};

extern BattleHandler BH;

#include "pch.h"
#include "BattleHandler.h"

BattleHandler::BattleHandler()
{
	
}

BattleHandler::~BattleHandler()
{
}

void BattleHandler::startBallte()
{
	battlefield = std::make_shared<Battlefield>();
	
	GH.pushWindow(battlefield);
}

sf::Vector2i BattleHandler::choseMoveDirection(BattleUnit* unit) const
{
	auto target = unit->target;
	sf::Vector2i velocity = { 0,0 };
	sf::Vector2i dir = sf::Vector2i(0, 0);
	if (target)
	{
		int count = 0;
		dir = unit->target->pos - unit->pos;
		if (dir.x > 0) velocity.x = 1;
		if (dir.x < 0) velocity.x = -1;
		if (dir.y < 0) velocity.y = -1;
		if (dir.y > 0) velocity.y = 1;
		
		while (!this->battlefield->containsIsBattlefield(unit->pos + velocity) ||
				battlefield->tiles[unit->pos.x + velocity.x][unit->pos.y + velocity.y].blocked)
		{
			int r = rand() % 4;
			switch (r)
			{
			case 0:
				if (dir.y == 0) velocity.y = 1;
				else velocity.y = 0;
				break;
			case 1:
				if (dir.y == 0) velocity.y = -1;
				else velocity.y = 0;
				break;
			case 2:
				if (dir.x == 0) velocity.x = -1;
				else velocity.x = 0;
				break;
			case 3:
				if (dir.x == 0) velocity.x = 1;
				else velocity.x = 0;
				break;
			}
			if (count++ > 10) {
				velocity = { 0,0 };
				break;
			}
		}
	}
	return velocity;
}

bool BattleHandler::nextToEachOther(BattleUnit* u1, BattleUnit* u2)
{
	if (!u1 || !u2) return false;
	// TODO implement case if unit is Big creature
	sf::Vector2i temp = u1->pos - u2->pos;
	if (abs(temp.x) <= 1 && abs(temp.y) <= 1)
		return true;
	return false;
}

BattleUnit* BattleHandler::findNeerestEnemy(BattleUnit* unit)
{
	BattleUnit* result = nullptr;
	float min = 9999;
	for (auto u : this->battlefield->units)
	{
		if (unit->enemy == u->enemy || !u->getAlive()) continue;
		float temp = pow(u->pos.x - unit->pos.x, 2.0);
		temp += pow(u->pos.y - unit->pos.y, 2.0);
		if (min > sqrt(temp)) result = u.get();
		min = std::min(min, sqrt(temp));
	}
	return result;
}

void BattleHandler::makeDecision(BattleUnit* unit)
{
	//if (!unit->target || !unit->target->alive)
	
	unit->target = this->findNeerestEnemy(unit);
	if (unit->getTarget() == nullptr) return;
	if (this->nextToEachOther(unit, unit->target))
		unit->makeAttack(unit->target->pos);
	else if (unit->shouter && unit->target)
		unit->makeShot(unit->target->pos);
	else
	{
		sf::Vector2i oldPos = unit->pos;
		auto move = this->choseMoveDirection(unit);
		unit->doMove(move); // set unit velocity
		this->battlefield->changeUnitPos(unit, oldPos, unit->pos + move);
	}
}

void BattleHandler::unitAttakced(BattleUnit* unit)
{
	auto target = unit->getTarget();
	int damage = this->calculateDamage(unit, target);
	target->reciveDamage(unit->pos);
	target->hp -= (int)damage;
	if (target->hp < 1)
		this->unitDied(target);
}

void BattleHandler::unitMadeShot(BattleUnit* unit)
{
	if(unit->target)
		unit->missle->setTarget(unit->target->pos);
}

void BattleHandler::unitDied(BattleUnit* unit)
{
	this->battlefield->tiles[unit->pos.x][unit->pos.y].blocked = false;
	this->battlefield->tiles[unit->pos.x][unit->pos.y].unit = nullptr;
	unit->dieing();
}

void BattleHandler::updateMissle(BattleUnit* unit)
{
	if (unit->missle && unit->missle->velocity != sf::Vector2f{0, 0})
	{
		auto pos = unit->missle->getTilePos();
		if (!this->battlefield->containsIsBattlefield(pos))
		{
			unit->missle = nullptr;
			return;
		}
		if (this->battlefield->tiles[pos.x][pos.y].unit &&
			this->battlefield->tiles[pos.x][pos.y].blocked &&
			this->battlefield->tiles[pos.x][pos.y].unit->enemy != unit->enemy)
		{
			auto target = this->battlefield->tiles[pos.x][pos.y].unit;
			target->reciveDamage(unit->pos);
			float damage = this->calculateDamage(unit, target);
			if(damage <= 3) target->makeBlock(unit->pos);
			else target->reciveDamage(unit->pos);
			target->hp -= (int)damage;
			if (target->hp < 1)
				this->unitDied(target);
			unit->missle = nullptr;
		}
	}
}

void BattleHandler::update(const float& dt)
{
	if (this->battlefield)
	{
		for (auto unit : this->battlefield->units)
		{
		
			unit->update(dt);
			if (unit->getAttacked())
			{
				this->unitAttakced(unit.get());
			}
			if (unit->getShooted())
			{
				this->unitMadeShot(unit.get());
			}
			this->updateMissle(unit.get());
			if(unit->animationState != AnimationState::ATTACKING &&
				unit->animationState != AnimationState::SHOOTHING &&
				unit->getAlive() &&
				!unit->moving)
			{
				//this->battlefield->changeUnitPos(unit->id,unit->pos,unit)
				this->makeDecision(unit.get());
			}
		}
			
	}
}

int BattleHandler::calculateDamage(BattleUnit* unit, BattleUnit* target)
{
	int distance =
		std::max(
			abs(unit->pos.x - target->pos.x),
			abs(unit->pos.y - target->pos.y));
	
	float damage = (float)unit->damage * (1 - 0.05 * (float)target->defence);
	if (distance > 15) damage * 0.5;
	if (damage < 1) damage = 1;
	return (int)damage;
}


BattleHandler BH = BattleHandler();
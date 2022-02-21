#include "BattleHandler.h"
#include "Battlefiled.h"

class Monster;
class Battlefield;
class Spell;
class InterfaceElem;
class Battlefield;
class BattleUnit;
class Player;

BattleHandler::BattleHandler()
{
	this->nuberUnitsInBattle[0] = 0;
	this->nuberUnitsInBattle[1] = 0;
}

BattleHandler::~BattleHandler()
{
}

void BattleHandler::startBallte(std::string path)
{
	if (!this->battlefield)
		battlefield = std::make_shared<Battlefield>(GameMode::Game);
	battlefield->load(path);
	this->initArmyQueque();
	this->battlefield->interactiveElem.push_back(this->battlefield);
	GH.pushWindow(this->battlefield);
}

void BattleHandler::spellCasted(Spell spell, Player* player)
{
	player->refreshColldown();
	if (!player->substrackMana(spellCost[spell.spell]))
		std::cout << "mana cannot be lower then 0!" << std::endl;
}

sf::Vector2i BattleHandler::choseMoveDirection(BattleUnit* unit) const
{

	sf::Vector2i velocity = { 0, 0 };
	sf::Vector2i dir = sf::Vector2i(0, 0);
	if (this->battlefield->containsIsBattlefield(unit->destenation))
	{
		int count = 0;
		dir = unit->destenation - unit->getPos();
		//unit->pathfinder->initializeGraph();
		//unit->pathfinder->calculatePaths();

		if ((unit->order == Order::AGRESIVE_STANCE || unit->order == Order::ATTACK) && unit->target)
		{
			// finding the neerest tile next to target
			unit->destenation = unit->getTarget()->getPos();
			for (auto item : unit->getTarget()->getNeighbourTilePos())
			{
				if (!this->battlefield->containsIsBattlefield(item) || this->battlefield->isTileBlocked(item))
					continue;
				if (unit->pathfinder->getNode(item)->getCost() < unit->pathfinder->getNode(unit->destenation)->getCost())
					unit->destenation = item;
			}
		}
		static const sf::Vector2i dirs[] = {
			sf::Vector2i(0, 0),sf::Vector2i(-1, +1), sf::Vector2i(0, +1), sf::Vector2i(+1, +1), sf::Vector2i(-1, +0),
			sf::Vector2i(+1, +0), sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(+1, -1),
			sf::Vector2i(-1, +2),sf::Vector2i(-2, +1), sf::Vector2i(0, +2), sf::Vector2i(+2, +1), sf::Vector2i(-2, +0),
			sf::Vector2i(+2, +0), sf::Vector2i(-2, -1), sf::Vector2i(0, -2), sf::Vector2i(+1, -2),sf::Vector2i(+1,+2)
		};
		Battle::BPath path;
		for (int i = 0; !unit->pathfinder->getPath(path, unit->destenation + dirs[i]) && i < 18; i++)
		{
			
			if(i > 16)
				std::cout << "cos nie ten z pathem" << std::endl;
		}
		bool checkBetterWay = true;
		for (int i = 0; i < path.nodes.size(); i++)
		{
			dir = this->length(path.nodes[i].coord - unit->getPos()) < this->length(dir) ? path.nodes[i].coord - unit->getPos() : dir;
			if (dir.x == 0 && dir.y == 0 && i > 0)
			{
				dir = path.nodes[i - 1].coord - unit->getPos();
				checkBetterWay = false;
				break;
			}
			
				//if (abs(dir.x) <= 1 && abs(dir.y) <= 1)
			//	break;
		}
		auto temp = (path.nodes.empty() ? unit->destenation : path.endPos()) - unit->getPos();
		if (length(temp) < length(temp - dir) +2 && checkBetterWay)
			dir = temp;
		if (path.nextPos() == sf::Vector2i(-1, -1))
		{
			unit->giveOrder(Order::AGRESIVE_STANCE);
		}
		/*std::cout<< " unit->getPos(): "<<unit->getPos().x<< " "<< unit->getPos().y<<std::endl;
		std::cout<< " dir: "<<dir.x<< " "<< dir.y<<std::endl;
		std::cout<< " dest: "<<unit->destenation.x<< " "<< unit->destenation.y<<std::endl;
		std::cout<< " path.nextPos() "<<path.nextPos().x<< " "<< path.nextPos().y<<std::endl;*/
		
		if (dir.x > 0)
			velocity.x = 1;
		if (dir.x < 0)
			velocity.x = -1;
		if (dir.y < 0)
			velocity.y = -1;
		if (dir.y > 0)
			velocity.y = 1;
		if (unit->moveMakeColision(velocity, this->battlefield) && unit->timeToUpdatePathfinder < 30 && unit->tryToMove > 4)
		{
			unit->giveOrder(Order::DEFENSIVE_POS);
			velocity = { 0, 0 };
		}
		else if (unit->moveMakeColision(velocity, this->battlefield))
		{
			velocity = { 0, 0 };
			unit->tryToMove++;
			unit->timeToUpdatePathfinder += 20;
		}
	}
		/*while (unit->moveMakeColision(velocity, this->battlefield))
		{
			switch (rand() % 4)
			{
				case 0:
					if (dir.y == 0)
						velocity.y = 1;
					else
						velocity.y = 0;
					break;
				case 1:
					if (dir.y == 0)
						velocity.y = -1;
					else
						velocity.y = 0;
					break;
				case 2:
					if (dir.x == 0)
						velocity.x = -1;
					else
						velocity.x = 0;
					break;
				case 3:
					if (dir.x == 0)
						velocity.x = 1;
					else
						velocity.x = 0;
					break;
				default:
					break;
			}
			if (count++ > 10)
			{
				velocity = { 0, 0 };
				break;
			}
		}
	}*/
	return velocity;
}

bool BattleHandler::nextToEachOther(BattleUnit* u1, BattleUnit* u2)
{
	if (!u1 || !u2)
		return false;
	for(auto tile : u2->getUsedTilesPos())
		if (u1->getNeighbourTilePos().find(tile) != u1->getNeighbourTilePos().end() )
			return true;
	for (auto tile : u1->getUsedTilesPos())
		if (u2->getNeighbourTilePos().find(tile) != u2->getNeighbourTilePos().end())
			return true;

	return false;
}

BattleUnit* BattleHandler::findNeerestEnemy(BattleUnit* unit)
{
	BattleUnit* result = nullptr;
	double min = 9999;
	for (auto u : this->battlefield->units)
	{
		if (unit->enemy == u->enemy || !u->getAlive())
			continue;
		double temp = pow(u->pos.x - unit->pos.x, 2.0);
		temp += pow(u->pos.y - unit->pos.y, 2.0);
		if (min > sqrt(temp))
			result = u.get();
		min = std::min(min, sqrt(temp));
	}
	return result;
}

BattleUnit* BattleHandler::calculateBestTargetFor(BattleUnit* unit)
{
	BattleUnit* result = nullptr;
	float max = -10000;
	for (auto u : this->battlefield->units)
	{
		if (!unit->isEnemyWith(u.get()) || !u->getAlive())
			continue;

		float cost = 10000;
			//unit->pathfinder->getNode(u->getPos())->getCost();
		for(auto pos: u->getUsedTilesPos())
			cost = std::min(cost, unit->pathfinder->getNode(pos)->getCost());
		float value = 100;
		value += (10.f * (float)u->damage * (1 / u->attackCoulddown)) - ((float)u->hp * 3.f);
		value += (float)u->attack - u->defence;
		value += u->speed * 0.1f;
		if (u->isShouter())
			value *= 1.2f;
		if (unit->isShouter())
			cost /= 10;
		value -= (cost / (unit->speed * 0.01f));
		if (max < value)
		{
			result = u.get();
			max = value;
		}
		
	}

	if(!result) 
		return this->findNeerestEnemy(unit);
	return result;
}

void BattleHandler::makeDecision(BattleUnit* unit)
{
	//if (!unit->target || !unit->target->alive)

	switch (unit->order)
	{
		case Order::DEFENSIVE_POS:
			this->handleDefenceStance(unit);
			break;
		case Order::AGRESIVE_STANCE:
			this->handleAggressiveStance(unit);
			break;
		case Order::ATTACK:
			this->handleAttackOrder(unit);
			break;
		case Order::MOVE:
			this->handleMoveOrder(unit);	
			break;
		default:
			;
	}
	unit->updateNeighbourPos();
}

void BattleHandler::unitAttakced(BattleUnit* unit)
{
	auto target = unit->getTarget();
	if (!target->getAlive())
		return;
	bool attackBlocked = false;
	if (target->haveDefensePosition())
	{
		if (rand() % 100 < ((target->defence < 0 ? 0 : target->defence) - unit->attack) * 3 + 50)
			attackBlocked = true;
	}
	else
	{
		if (rand() % 100 < ((target->defence < 0 ? 0 : target->defence) - unit->attack) * 3 )
			attackBlocked = true;
	}
	int damage = this->calculateDamage(unit, target, attackBlocked);
	if (attackBlocked)
		target->makeBlock(unit->pos, damage);
	else
		target->reciveDamage(unit->pos, damage);
	target->hp -= damage;
	if (target->alive && !target->getAlive())
		this->unitKilled(target);
}

void BattleHandler::unitMadeShot(BattleUnit* unit)
{
	if (unit->target)
		unit->missle->setTarget(unit->target);
}

void BattleHandler::unitKilled(BattleUnit* unit)
{
	for (auto pos : unit->getUsedTilesPos())
	{
		this->battlefield->getTile(pos).blocked = false;
		this->battlefield->getTile(pos).unit = nullptr;
	}
	unit->dieing();
	if (unit->isEnemy())
		this->nuberUnitsInBattle[1]--;
	else
		this->nuberUnitsInBattle[0]--;
}

void BattleHandler::updateMissle(BattleUnit* unit)
{
	if (unit->missle && unit->missle->velocity != sf::Vector2f { 0, 0 })
	{
		auto pos = unit->missle->getTilePos();
		if (!this->battlefield->containsIsBattlefield(pos))
		{
			unit->missle = nullptr;
			return;
		}
		if (this->battlefield->getTile(pos).unit && this->battlefield->isTileBlocked(pos) && this->battlefield->getTile(pos).unit->enemy != unit->enemy)
		{
			auto target = this->battlefield->getTile(pos).unit;
			bool attackBlocked = false;
			if (target->haveDefensePosition())
			{
				if (rand() % 100 < ((target->defence < 0 ? 0 : target->defence) - unit->attack) * 3 + 50)
					attackBlocked = true;
			}
			else
			{
				if (rand() % 100 < ((target->defence < 0 ? 0 : target->defence) - unit->attack) * 3)
					attackBlocked = true;
			}

			int damage = this->calculateDamage(unit, target, attackBlocked);
			if (attackBlocked)
				target->makeBlock(unit->pos, damage);
			else
				target->reciveDamage(unit->pos, damage);
			target->hp -= (int)damage;
			if (target->alive && !target->getAlive())
				this->unitKilled(target);
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
			if (this->battlefield->gamePaused)
				unit->update(0.f);
			else
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
			if (unit->animationState != AnimationState::ATTACKING && unit->animationState != AnimationState::SHOOTHING && unit->animationState != AnimationState::RECIVING_DMG && unit->animationState != AnimationState::BLOCKING && unit->getAlive() && !unit->moving)
			{
				//this->battlefield->changeUnitPos(unit->id,unit->pos,unit)
				if (!this->battlefield->gamePaused)
					this->makeDecision(unit.get());
			}
		}
		this->updateQueque();

		if ((this->nuberUnitsInBattle[0] <= 0 && this->armyQueque[0].empty())
			|| (this->nuberUnitsInBattle[1] <= 0 && this->armyQueque[1].empty()))
		{
			std::shared_ptr<WindowObject> win;
			win = std::make_shared<WindowObject>(400, 200, 600, 400, GH.globalFont);
			
			if (this->nuberUnitsInBattle[0] > 0)
				win->addText("Player1 won:", { 250, 10 });
			else
				win->addText("Player2 won:", { 250, 10 });

			win->addText("Battle Result", { 240, 40 });

			for (int i = 0; i < 2; i++)
				if (this->battlefield->players[i]->isAI())
					win->addText("Player" + std::to_string(i + 1) + "(AI) lost:", { 10 + i * 360.f, 70 });
				else
					win->addText("Player" + std::to_string(i + 1) + " lost:", { 10 + i * 360.f, 70 });

			float i = 0, j = 0;
			for (auto type : allMonseters2)
			{
				int number[2] = { 0, 0 };
				for (auto creature : this->battlefield->units)
				{
					if (creature->getType() == type && !creature->getAlive())
						number[creature->enemy]++;
				}
				if (number[0] != 0)
				{
					win->addText(creatureToString[type] + "\t " + std::to_string(number[0]), { 10, 100 + i });
					i += 24;
				}
				if (number[1] != 0)
				{
					win->addText(creatureToString[type] + "\t " + std::to_string(number[1]), { 370, 100 + j });
					j += 24;
				}
			}

			win->buttons["OK"] = std::make_shared<Button>(400 + 550, 160 + 400, 40, 40, &win->font, "OK");
			win->buttons["OK"]->addFuctionallity([=]() {
				win->close();
				auto playerWon = this->nuberUnitsInBattle[0] > 0;
				if (playerWon)
					Config.unlockNextLevel(battlefield->level + 1);
				battlefield->close();
			});
			win->interactiveElem.push_back(win->buttons["OK"]);
			GH.Get().pushWindow(win);
		}
	}
}

void BattleHandler::handleAggressiveStance(BattleUnit* unit)
{
	bool result;
	auto target = this->calculateBestTargetFor(unit);
	unit->choseTarget(target);
			
	if (this->nextToEachOther(unit, unit->target))
	{
		result = unit->makeAttack(unit->target->getPos());
		if (result == false)
			unit->idle();
	}
	else if (unit->shooter && unit->target && unit->arrows > 0)
	{
		result = unit->makeShot(unit->target->pos);
		if (result == false)
			unit->idle();
	}
	else
	{
		sf::Vector2i oldPos = unit->getPos();
		auto move = this->choseMoveDirection(unit);
		unit->doMove(move); // set unit velocity
		this->battlefield->changeUnitPos(unit, oldPos, unit->pos + move);
		
	} 
}

//It can be more clear
void BattleHandler::handleDefenceStance(BattleUnit* unit)
{
	if (this->battlefield->players[1]->isAI() && unit->isEnemy())
		unit->giveOrder(Order::AGRESIVE_STANCE);
	bool result;

	auto target = this->calculateBestTargetFor(unit);
	unit->choseTarget(target);

	if (this->nextToEachOther(unit, unit->target))
	{
		result = unit->makeAttack(unit->target->getPos());
		if (result == false)
			unit->idle();
	}
	else
	{
		//check if there is enemy next to unit
		for(auto u : this->battlefield->units)
		{
			if(u && u->getAlive() && unit->isEnemyWith(u.get()))
				if (this->nextToEachOther(unit, u.get()))
				{
					unit->choseTarget(u.get());
					result = unit->makeAttack(u->getPos());
					if (result == false)
						unit->idle();
					break;
				}
		}
	}
	
}

void BattleHandler::handleAttackOrder(BattleUnit* unit)
{
	bool result;
	if (unit->target == nullptr)
	{
		unit->giveOrder(Order::AGRESIVE_STANCE);
		return;
	}
	if (this->nextToEachOther(unit, unit->target))
	{
		result = unit->makeAttack(unit->target->getPos());
		if (result == false)
			unit->idle();
	}
	else if (unit->shooter && unit->arrows > 0)
	{
		result = unit->makeShot(unit->target->pos);
		if (result == false)
			unit->idle();
	}
	else
	{
		sf::Vector2i oldPos = unit->getPos();
		auto move = this->choseMoveDirection(unit);
		unit->doMove(move); // set unit velocity
		this->battlefield->changeUnitPos(unit, oldPos, unit->pos + move);
	}
	if (!unit->target->getAlive()) 
		unit->giveOrder(Order::AGRESIVE_STANCE);
}


void BattleHandler::handleMoveOrder(BattleUnit* unit)
{
	auto& neighbourTiles = unit->getNeighbourTilePos();
	if(neighbourTiles.find(unit->destenation) != neighbourTiles.end() && battlefield->getTile(unit->destenation).blocked)
		unit->giveOrder(Order::DEFENSIVE_POS);
	else if(unit->destenation != unit->getPos2() && unit->destenation != unit->getPos())
	{
		sf::Vector2i oldPos = unit->getPos();
		auto move = this->choseMoveDirection(unit);
		unit->doMove(move); // set unit velocity
		this->battlefield->changeUnitPos(unit, oldPos, unit->pos + move);
	}
	else
		unit->giveOrder(Order::DEFENSIVE_POS);
}

double BattleHandler::length(sf::Vector2i vec) const
{
	return pow(vec.x, 2.0) + pow(vec.y, 2.0);
}

int BattleHandler::calculateDamage(BattleUnit* unit, BattleUnit* target, bool attackBlocked)
{
	int distance =
		std::max(
			abs(unit->pos.x - target->pos.x),
			abs(unit->pos.y - target->pos.y));

	float damage = (float)unit->damage;
	if (attackBlocked)
		damage /= 2;
	if (damage < 1)
		damage = 1;
	return (int)std::round(damage);
}

void BattleHandler::initArmyQueque()
{
	this->nuberUnitsInBattle[0] = 0;
	this->nuberUnitsInBattle[1] = 0;
	while (!this->armyQueque[0].empty())
		this->armyQueque[0].pop();
	while (!this->armyQueque[1].empty())
		this->armyQueque[1].pop();

	for (int j = 0; j < 2; j++)
	{
		bool setAllArmy = false;
		while (!setAllArmy)
		{
			setAllArmy = true;
			for (int i = 0; i < 7; i++)
			{
				if (this->battlefield->players[j]->army[i].monster == Monster::NO_CREATURE || this->battlefield->players[j]->army[i].count < 1)
					continue;
				this->armyQueque[j].push(this->battlefield->players[j]->army[i].monster);
				this->battlefield->players[j]->army[i].count--;
				setAllArmy = false;
			}
		}
	}
}

void BattleHandler::updateQueque()
{
	for (int i = 0; i < 2; i++)
	{

		if (!this->armyQueque[i].empty() && this->nuberUnitsInBattle[i] < 8)
		{
			Monster creature = this->armyQueque[i].front();
			sf::Vector2i pos;
			int conut = 0;
			do
			{
				int temp = rand() % Config.battlefiledTileHegiht;
				pos = { i * (Config.battlefiledTileWidth - creaturesStats[creature].size.x) , temp };
			} while (this->battlefield->isTileBlocked(pos) && conut++ < 60);

			if(this->battlefield->addUnit(std::make_shared<BattleUnit>(creature), pos, (bool)i))
			{
				this->nuberUnitsInBattle[i]++;
				this->armyQueque[i].pop();
			}
		}
	}
	battleBegan = true;
}

BattleHandler BH = BattleHandler();

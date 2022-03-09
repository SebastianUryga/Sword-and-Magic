#include "GuiHandler.h"

class BattleUnit;

void BattleUnit::initAnimation()
{
	this->spellEffectAnimation =
		new AnimationComponent(this->spellEffect, *graphics.battleEffectsSheet);
	for (auto s : allSpells)
	{
		struct EffectsAnimationParametrs stat = batteEffectsAnimationParamets[s];
		this->spellEffectAnimation->addAnimotion(
			spellToString[s], stat.animationTimer, stat.start_frame_x, stat.start_frame_y, stat.frames_x, stat.frames_y, stat.width, stat.height, false, { 6, 50 }, stat.tileWidth);
	}

	this->animation =
		new AnimationComponent(this->sprite, *graphics.battleUnitsSheets[this->type]);
	struct MonsterAnimationParametrs stat =
		animationParametrs[{ type, "IDLE" }];
	this->animation->addAnimotion("IDLE",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	this->sprite.setOrigin(stat.orgin);
	stat = animationParametrs[{ type, "START_MOVE" }];
	this->animation->addAnimotion("START_MOVE",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		true,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "MOVE1" }];
	this->animation->addAnimotion("MOVE1",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "MOVE2" }];
	this->animation->addAnimotion("MOVE2",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "ATTACK_UP" }];
	this->animation->addAnimotion("ATTACK_UP",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "ATTACK" }];
	this->animation->addAnimotion("ATTACK",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "ATTACK_DOWN" }];
	this->animation->addAnimotion("ATTACK_DOWN",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "DAMAGED" }];
	this->animation->addAnimotion("DAMAGED",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "BLOCK" }];
	this->animation->addAnimotion("BLOCK",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "DIE" }];
	this->animation->addAnimotion("DIE",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		true,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "SHOT_UP" }];
	this->animation->addAnimotion("SHOT_UP",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "SHOT" }];
	this->animation->addAnimotion("SHOT",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
	stat = animationParametrs[{ type, "SHOT_DOWN" }];
	this->animation->addAnimotion("SHOT_DOWN",
		stat.animationTimer,
		stat.start_frame_x,
		stat.start_frame_y,
		stat.frames_x,
		stat.frames_y,
		stat.width,
		stat.height,
		false,
		stat.orgin,
		stat.tileWidth);
}

void BattleUnit::initStatistic()
{
	struct MonsterStats stats = creaturesStats[type];
	this->bigCreature = stats.bigCreature;
	this->shooter = stats.archer;
	this->maxHp = stats.hp;
	this->hp = this->maxHp;
	this->arrows = stats.arrows;
	this->damage = stats.damage;
	this->attack = stats.attack;
	this->defence = stats.defence;
	this->attackCoulddown = 1 / stats.attackSpeed;
	this->speed = (float)(rand() % 4) + stats.speed;
}

void BattleUnit::initTextDmg(const int dmg)
{
	//initializate number of damge to display
	DamageText text;
	text.displayTimeRemain = 1.f;
	text.number = sf::Text(std::to_string(dmg), GH.globalFont, 20);
	text.number.setPosition(this->sprite.getPosition() + sf::Vector2f(20, -20));
	this->damageTexts.push_back(text);
}
// TODO Make tests for it
bool BattleUnit::moveMakeColision(const sf::Vector2i& moveDirection, const std::shared_ptr<Battlefield> battlefield) const
{
	if (moveDirection == sf::Vector2i { 0, 0 })
		return false;
	bool result = battlefield->isTileBlocked(this->getPos() + moveDirection);
	if (bigCreature)
	{
		if (result && this->getPos() + moveDirection == this->getPos2())
		{
			return battlefield->isTileBlocked(this->getPos2() + moveDirection);
		}
		if (this->getPos2() + moveDirection == this->getPos())
			return result;
	}
	return result || battlefield->isTileBlocked(this->getPos2() + moveDirection);
}

bool BattleUnit::isShouter() const
{
	return this->shooter;
}

bool BattleUnit::isBig() const
{
	return this->bigCreature;
}

TileSet& BattleUnit::getNeighbourTilePos()
{
	return this->neighbourTilePos;
}

sf::Vector2i BattleUnit::getPos() const
{
	return this->pos;
}

sf::Vector2i BattleUnit::getPos2() const
{
	return this->pos2;
}

BattleUnit* BattleUnit::getTarget() const
{
	return this->target;
}

bool BattleUnit::getAttacked()
{
	if (this->attacked)
	{
		this->attacked = false;
		this->actualAttackCoulddown = this->attackCoulddown;
		return true;
	}
	return this->attacked;
}

bool BattleUnit::getShooted()
{
	if (this->shooted)
	{
		this->shooted = false;
		this->actualAttackCoulddown = this->attackCoulddown;
		this->missle = std::make_shared<Missle>(this);
		this->arrows--;
		return true;
	}
	return this->shooted;
}

bool BattleUnit::getAlive() const
{
	if (this->hp <= 0)
		return false;
	return true;
}

Monster BattleUnit::getType() const
{
	return this->type;
}

bool BattleUnit::isEnemy() const
{
	return this->enemy;
}

bool BattleUnit::isEnemyWith(const BattleUnit* unit) const
{
	return this->enemy != unit->enemy;
}

bool BattleUnit::haveDefensePosition() const
{
	if (this->animationState == AnimationState::IDLE || this->animationState == AnimationState::BLOCKING)
		return true;
	else
		return false;
}

void BattleUnit::idle()
{
	this->attacking = false;
	this->animationState = AnimationState::IDLE;
	this->velocity = sf::Vector2f(0, 0);
}

void BattleUnit::doMove(sf::Vector2f direction)
{
	if (direction != sf::Vector2f(0, 0))
	{
		this->moving = true;
		if (this->animationState != AnimationState::MOVING)
		{
			this->animationState = AnimationState::START_MOVING;
			this->moving2 = false;
		}
		else
			this->animationState = AnimationState::MOVING;
		if (direction.x > 0)
			this->lastDirection = false;
		if (direction.x < 0)
			this->lastDirection = true;
	}

	if (abs(direction.x) == 1 && abs(direction.y) == 1)
		direction /= 1.41f;
	this->setVelocity(direction);
}

bool BattleUnit::makeAttack(const sf::Vector2i target)
{
	if (this->animationState == AnimationState::ATTACKING)
		return false;
	if (this->actualAttackCoulddown > 0)
		return false;
	if (pos.x < target.x)
		this->lastDirection = false;
	if (pos.x > target.x)
		this->lastDirection = true;
	this->animationState = AnimationState::ATTACKING;
	this->attacked = false;
	return true;
}

bool BattleUnit::makeShot(const sf::Vector2i target)
{
	if (!this->shooter)
		return false;
	if (this->animationState == AnimationState::SHOOTHING)
		return false;
	if (this->actualAttackCoulddown > 0)
		return false;
	if (pos.x < target.x)
		this->lastDirection = false;
	if (pos.x > target.x)
		this->lastDirection = true;
	this->animationState = AnimationState::SHOOTHING;
	this->shooted = false;
	return true;
}

void BattleUnit::reciveDamage(const sf::Vector2i from, const int dmg)
{
	this->initTextDmg(dmg);

	if (this->animationState == AnimationState::RECIVING_DMG || (dmg * 100) / this->maxHp < 20)
		return;
	if (pos.x < from.x)
		this->lastDirection = false;
	if (pos.x > from.x)
		this->lastDirection = true;
	this->animationState = AnimationState::RECIVING_DMG;
}

void BattleUnit::makeBlock(const sf::Vector2i from, const int dmg)
{
	this->initTextDmg(dmg);

	if (this->animationState == AnimationState::BLOCKING || (dmg * 100) / this->maxHp < 10)
		return;
	if (pos.x < from.x)
		this->lastDirection = false;
	if (pos.x > from.x)
		this->lastDirection = true;
	this->animationState = AnimationState::BLOCKING;
}

void BattleUnit::dieing()
{
	if (this->animationState == AnimationState::DIEING)
		return;
	this->animationState = AnimationState::DIEING;
}

void BattleUnit::fixSpritePos()
{

	sf::Vector2f fixedPos = this->sprite.getPosition();
	
	fixedPos = (sf::Vector2f)(this->getPos() + sf::Vector2i{1, 3}) *B_TILE_WIDTH;
	this->sprite.setPosition(fixedPos);
	this->spellEffect.setPosition(fixedPos);
	this->lineHP.setPosition(fixedPos - sf::Vector2f { 0, 50 });
	this->text.setPosition(fixedPos - sf::Vector2f(0, 60));
}

bool BattleUnit::giveDestenation(sf::Vector2i des)
{
	this->destenation = des;
	return true;
}

bool BattleUnit::choseTarget(BattleUnit* t)
{
	if (t && t->isEnemy() == this->isEnemy())
		return false;

	this->target = t;
	return true;
}

void BattleUnit::setPathfinder(Battlefield* field)
{
	this->pathfinder = std::make_shared<Battle::PathFinder>(field, this);
	this->timeToUpdatePathfinder = 100;
}

void BattleUnit::setPos(sf::Vector2i pos)
{
	if (!this->moving)
	{
		this->sprite.setPosition(pos.x * B_TILE_WIDTH + 50, pos.y * B_TILE_HEIGHT + 150);
		this->spellEffect.setPosition(pos.x * B_TILE_WIDTH + 50, pos.y * B_TILE_HEIGHT + 150);
		this->lineHP.setPosition(pos.x * B_TILE_WIDTH + 50, pos.y * B_TILE_HEIGHT + 100);
		this->text.setPosition(sprite.getPosition() - sf::Vector2f(0, 60));
	}
	this->shape.left = pos.x * B_TILE_WIDTH + 50;
	this->shape.top = pos.y * B_TILE_HEIGHT + 150;
	this->pos = pos;
	this->pos2.y = pos.y;
	if (this->bigCreature)
		this->pos2.x = pos.x - 1;
	else
		this->pos2 = pos;
}

void BattleUnit::setVelocity(sf::Vector2f direction)
{
	this->velocity = direction;
}

void BattleUnit::setEnemy(bool enemy)
{
	this->enemy = enemy;
}

void BattleUnit::giveOrder(Order order)
{
	this->order = order;
}

void BattleUnit::clickLeft([[maybe_unused]] bool down, [[maybe_unused]] bool previousState)
{
}

BattleUnit::BattleUnit(Monster type) :
	InterfaceElem(),
	type(type),
	velocity(sf::Vector2f(0, 0)),
	alive(true),
	enemy(false)
{
	this->initAnimation();
	this->initStatistic();
	this->target = nullptr;
	this->order = Order::AGRESIVE_STANCE;
	this->spellToAnimate = Spell::SpellType::NONE;
	this->destenation = { 0, 0 };
	this->attacking = false;
	this->attacked = false;
	this->reverseAttaking = false;
	this->shooted = false;
	this->recivingDamage = false;
	this->moving = false;
	this->moving2 = false;
	this->offset = { 100, 100 };
	this->actualAttackCoulddown = (float)(rand() % 73) / 21.f;
	this->shape.top = sprite.getPosition().y;
	this->shape.left = sprite.getPosition().x;
	this->shape.height = 90;
	this->shape.width = 50;
	this->lineHP.setFillColor(sf::Color::Green);
	this->lineHP.setSize(sf::Vector2f(50, 3));
	this->text.setFont(GH.globalFont);
	this->text.setCharacterSize(12);
	this->updateNeighbourPos();
}

BattleUnit::~BattleUnit()
{
}

void BattleUnit::updatePathfinder(const float& dt)
{
	this->timeToUpdatePathfinder += dt * this->speed;
	if (timeToUpdatePathfinder > 100)
	{
		this->pathfinder->initializeGraph();
		this->pathfinder->calculatePaths();
		this->timeToUpdatePathfinder = 0;
	}
}

void BattleUnit::updateNeighbourPos()
{
	this->neighbourTilePos.clear();
	static const sf::Vector2i dirs[] = {
		sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(+1, -1), sf::Vector2i(-1, +0), /* source pos */ sf::Vector2i(+1, +0), sf::Vector2i(-1, +1), sf::Vector2i(0, +1), sf::Vector2i(+1, +1)
	};
	for (int i = 0; i < 8; i++)
	{
		if (neighbourTilePos.find(this->pos + dirs[i]) == neighbourTilePos.end())
			neighbourTilePos.insert(this->pos + dirs[i]);

		if (neighbourTilePos.find(this->pos2 + dirs[i]) == neighbourTilePos.end())
			neighbourTilePos.insert(this->pos2 + dirs[i]);
	}
}

void BattleUnit::updateAnimation(const float& dt)
{
	std::string action = "IDLE";
	bool playReversly = false;
	switch (this->animationState)
	{
		case AnimationState::IDLE:
			action = "IDLE";
			break;
		case AnimationState::START_MOVING:
			action = "START_MOVE";
			if (this->animation->playedOnce(action))
			{
				this->animationState = AnimationState::MOVING;
				return;
			}
			break;
		case AnimationState::MOVING: {
			action = "MOVE";
			if (this->moving2)
				action += "2";
			else
				action += "1";
			if (this->animation->playedOnce(action))
			{
				this->moving2 = !this->moving2;
				return;
			}
			break;
		}
		case AnimationState::END_MOVEING:
			action = "END_MOVE";
			break;
		case AnimationState::SHOOTHING: {
			if (!this->target)
				break;
			action = "SHOT";
			std::string dirShot = "_UP";
			sf::Vector2i dir = this->target->pos - this->pos;
			if (dir.x <= -dir.y && dir.x >= dir.y)
				dirShot = "_UP";
			else if (dir.x < dir.y && dir.x >= -dir.y)
				dirShot = "_DOWN";
			else
				dirShot = "";
			action += dirShot;
			if (this->animation->playedOnce(action)
				&& this->actualAttackCoulddown <= 0)
				this->shooted = true;
			break;
		}
		case AnimationState::ATTACKING: {
			if (!this->target)
				break;
			action = "ATTACK";
			std::string dirAtack = "";
			sf::Vector2i dir = this->target->pos - this->pos;
			if (dir.y < 0)
				dirAtack = "_UP";
			if (dir.y == 0)
				dirAtack = "";
			if (dir.y > 0)
				dirAtack = "_DOWN";
			action += dirAtack;
			if (this->animation->playedHalf(action)
				&& this->actualAttackCoulddown <= 0)
				this->attacked = true;
			break;
		}
		case AnimationState::BLOCKING:
			action = "BLOCK";
			if (this->animation->playedOnce(action) && !playReversly)
				playReversly = true;
			break;
		case AnimationState::RECIVING_DMG:
			action = "DAMAGED";
			if (this->animation->playedOnce(action))
				this->recivingDamage = false;
			break;
		case AnimationState::DIEING:
			action = "DIE";
			if (this->animation->playedOnce(action))
				this->alive = false;
			break;
		default:
			break;
	}
	this->text.setString(action);
	if (
		this->animationState == AnimationState::MOVING || this->animationState == AnimationState::IDLE || (this->animationState == AnimationState::BLOCKING && !playReversly))
		this->animation->play(action, dt, this->lastDirection);
	else if (!this->animation->playedOnce(action))
		this->animation->play(action, dt, this->lastDirection, playReversly);
	else
		this->animationState = AnimationState::IDLE;
}

void BattleUnit::update(const float& dt)
{
	if (this->alive)
		this->updateAnimation(dt);
	this->updatePathfinder(dt);
	if (this->spellToAnimate.spell != Spell::SpellType::NONE)
	{
		if (spellEffectAnimation->playedOnce(spellToString[this->spellToAnimate.spell]))
			this->spellToAnimate.spell = Spell::SpellType::NONE;
		else
			spellEffectAnimation->play(spellToString[this->spellToAnimate.spell], dt, false);
	}
	for (auto& s : this->castedSpellList)
	{
		s.timeRemain -= dt;

		if (s.timeRemain < 0)
		{
			Spell::takeOffSpellFromUnit(*this, s.type);
			break;
		}
	}
	if (shooter && missle)
		this->missle->update(dt);
	if (actualAttackCoulddown > 0)
		actualAttackCoulddown -= dt;
	if (Order::ATTACK == this->order && !target->getAlive())
		this->giveOrder(Order::AGRESIVE_STANCE);
	sf::Vector2f toMove = this->velocity * dt * this->speed;
	this->sprite.move(toMove);
	this->spellEffect.move(toMove);
	this->lineHP.move(toMove);
	this->text.move(toMove);
	this->offset += (toMove);
	if (B_TILE_WIDTH < abs(this->offset.x) || B_TILE_HEIGHT < abs(this->offset.y))
	{
		this->moving = false;
		//this->moving2 = false;
		if (this->order == Order::DEFENSIVE_POS)
			this->idle();
		this->offset = { 0, 0 };
		setVelocity(sf::Vector2f(0, 0));
		this->fixSpritePos();
	}
	if (!this->damageTexts.empty())
	{
		auto it = this->damageTexts.begin();

		for (size_t i = 0; i < this->damageTexts.size(); i++)
		{
			it->displayTimeRemain -= dt;
			it->number.move(0, -1 * dt * 50);
			if (it->displayTimeRemain <= 0)
			{
				this->damageTexts.erase(it);
				break;
			}
			it++;
		}
	}

	if (hp < 1)
	{
		hp = 0;
	}
	this->lineHP.setSize(sf::Vector2f(50 * ((float)hp / (float)maxHp), 3));
}

void BattleUnit::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	if (this->shooter && this->missle)
		this->missle->render(target);
	if (this->spellToAnimate.spell != Spell::SpellType::NONE)
		target->draw(this->spellEffect);
	target->draw(this->lineHP);
	target->draw(text);
	for (auto text : this->damageTexts)
		target->draw(text.number);
}

Missle::Missle(BattleUnit* unit) :
	speed(800.f),
	startingPos(unit->getPos())
{
	//this->sprite.setTexture(*graphics.battleUnitsSheets[type]);
	//this->sprite.setTextureRect(sf::IntRect(400, 400, 30, 30));
	this->shape = sf::RectangleShape(sf::Vector2f(10, 10));
	this->shape.setFillColor(sf::Color::Yellow);
	this->shape.setPosition((sf::Vector2f)unit->getPos() * B_TILE_HEIGHT);
	this->shape.move(70, 170);
	this->velocity = { 0, 0 };
}

Missle::~Missle()
{
}

void Missle::setTarget(sf::Vector2i targetPos)
{
	sf::Vector2i dir = targetPos - this->startingPos;
	float temp;
	if (abs(dir.x) > abs(dir.y))
		temp = 1.f / dir.x;
	else
		temp = 1.f / dir.y;
	this->velocity.x = dir.x * abs(temp);
	this->velocity.y = dir.y * abs(temp);
}

sf::Vector2i Missle::getTilePos() const
{
	return (sf::Vector2i)((this->shape.getPosition() - sf::Vector2f(50, 150)) / B_TILE_WIDTH);
}

void Missle::update(const float& dt)
{

	this->shape.move(this->velocity * speed * dt);
}

void Missle::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

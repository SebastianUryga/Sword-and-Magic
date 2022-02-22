#include "BattleUnit.h"
#include "BattleHandler.h"
#include "CreatureInfo.h"

class BattleUnit;

void BattleUnit::initAnimation2()
{
	if (graphics2.creaturesTextures.find(this->type) == graphics2.creaturesTextures.end())
	{
		this->sprite.setScale(0.5f, 0.5f);
		
		this->animator = std::make_shared<Animator>(this->sprite);
		animator->addAnimotion("IDLE", graphics2.creaturesTextures[Monster::ORK1].idle,
			0.8f, 340, 120, sf::Vector2f(150, 160), Config.tileWidth + 20);
		animator->addAnimotion("MOVE", graphics2.creaturesTextures[Monster::ORK1].move,
			0.8f, 340, 120, sf::Vector2f(150, 160), Config.tileWidth + 20);
		animator->addAnimotion("ATTAK", graphics2.creaturesTextures[Monster::ORK1].attak,
			1.f, 340, 120, sf::Vector2f(150, 160), Config.tileWidth + 20);
		animator->addAnimotion("DIE", graphics2.creaturesTextures[Monster::ORK1].die,
			1.f, 340, 120, sf::Vector2f(150, 160), Config.tileWidth + 20);
		animator->addAnimotion("RUN", graphics2.creaturesTextures[Monster::ORK1].run,
			1.f, 340, 120, sf::Vector2f(150, 160), Config.tileWidth + 20);
		animator->addAnimotion("HURT", graphics2.creaturesTextures[Monster::ORK1].hurt,
			1.f, 340, 120, sf::Vector2f(150, 160), Config.tileWidth + 20);

	}
	else
	{
		auto scalar = (2 * Config.tileWidth) / 130.f;
		this->sprite.setScale(scalar, scalar);
		this->spellEffect.setScale(scalar, scalar);
		this->animator = std::make_shared<Animator>(this->sprite);
		animator->addAnimotion("IDLE", graphics2.creaturesTextures[this->type].idle,
			0.9f, 340, 120, creatureTexturesOffest[this->type], 65.f * this->usedTiles.x);
		animator->addAnimotion("MOVE", graphics2.creaturesTextures[this->type].move,
			0.8f, 340, 120, creatureTexturesOffest[this->type], 65.f * this->usedTiles.x);
		animator->addAnimotion("ATTAK", graphics2.creaturesTextures[this->type].attak,
			0.8f, 340, 120, creatureTexturesOffest[this->type], 65.f * this->usedTiles.x);
		animator->addAnimotion("DIE", graphics2.creaturesTextures[this->type].die,
			0.8f, 340, 120, creatureTexturesOffest[this->type], 65.f * this->usedTiles.x);
		animator->addAnimotion("RUN", graphics2.creaturesTextures[this->type].run,
			0.8f, 340, 120, creatureTexturesOffest[this->type], 65.f * this->usedTiles.x);
		animator->addAnimotion("HURT", graphics2.creaturesTextures[this->type].hurt,
			0.6f, 340, 120, creatureTexturesOffest[this->type], 65.f * this->usedTiles.x);
	}
	/*this->spellEffectAnimation =
		std::make_shared<AnimationComponent>(this->spellEffect, *graphics2.battleEffectsSheet);
	for (auto s : allSpells)
	{
		struct EffectsAnimationParametrs stat = batteEffectsAnimationParamets[s];
		this->spellEffectAnimation->addAnimotion(
			spellToString[s], stat.animationTimer, stat.start_frame_x, stat.start_frame_y, stat.frames_x, stat.frames_y, stat.width, stat.height, false, { 6, 50 }, Config.tileWidth);
	}*/
}

void BattleUnit::initAnimation()
{
	
	this->spellEffectAnimation =
		std::make_shared<AnimationComponent>(this->spellEffect, *graphics.battleEffectsSheet);
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
	this->usedTiles = stats.size;
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
	sf::Vector2i temp;

	if (moveDirection.x > 0)
	{
		for (int y = 0; y < getSize().y; y++)
		{
			temp = this->pos + moveDirection + sf::Vector2i(getSize().x - 1, y);
			if (battlefield->isTileBlocked(temp))
				return true;
		}
	}
	if (moveDirection.y > 0)
	{
		for (int x = 0; x < getSize().x; x++)
		{
			temp = this->pos + moveDirection + sf::Vector2i(x, getSize().y - 1);
			if (battlefield->isTileBlocked(temp))
				return true;
		}
	}
	if (moveDirection.x < 0)
	{
		for (int y = 0; y < getSize().y; y++)
		{
			temp = this->pos + moveDirection + sf::Vector2i(0, y);
			if (battlefield->isTileBlocked(temp))
				return true;
		}
	}
	if (moveDirection.y < 0)
	{
		for (int x = 0; x < getSize().x; x++)
		{
			temp = this->pos + moveDirection + sf::Vector2i(x, 0);
			if (battlefield->isTileBlocked(temp))
				return true;
		}
	}
	return false;
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

TileSet BattleUnit::getUsedTilesPos()
{
	auto set = TileSet();
	for (int x = 0; x < this->usedTiles.x; x++)
		for (int y = 0; y < this->usedTiles.y; y++)
			set.insert(sf::Vector2i(this->getPos() + sf::Vector2i(x, y)));
	return set;
}

bool BattleUnit::containsPos(sf::Vector2i pos)
{
	auto set = getUsedTilesPos();
	return set.find(pos) != set.end();
}

sf::Vector2i BattleUnit::getSize() const
{
	return this->usedTiles;
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

Order BattleUnit::getOrder() const
{
	return this->order;
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

int BattleUnit::getActualHp() const
{
	return hp;
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

void BattleUnit::doMove(sf::Vector2i direction)
{
	if (direction != sf::Vector2i(0, 0))
	{
		this->tryToMove = 0;
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
	if (isBlid) Spell::takeOffSpellFromUnit(*this, Spell::SpellType::TURN_TO_STONE);
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
	auto fixedPos = sf::Vector2f(
		this->getPos().x * Config.tileWidth,
		this->getPos().y * Config.tileHeight) + Config.battlefieldOffset;
	this->sprite.setPosition(fixedPos);
	this->shape.top = this->sprite.getPosition().y - (creatureTexturesOffest[this->type].y / 2.f) *this->sprite.getScale().y;
	this->shape.left = this->sprite.getPosition().x + 10 * this->sprite.getScale().y;
	this->shape.height = 180 * this->sprite.getScale().y;
	this->shape.width = 50.f*this->getSize().x * this->sprite.getScale().y;
	this->rect.setPosition(shape.left, shape.top);
	this->rect.setSize(sf::Vector2f((float)shape.width, (float)shape.height));
	this->spellEffect.setPosition(fixedPos - sf::Vector2f(0, Config.tileHeight + 15));
	this->lineHP.setPosition(shape.left-5, shape.top);
	this->text.setPosition(fixedPos - sf::Vector2f(0, Config.tileHeight + 15));
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
	this->timeToUpdatePathfinder = 200;
}

void BattleUnit::setPos(sf::Vector2i tilePos)
{
	auto pixelPos = sf::Vector2f(
		tilePos.x  * Config.tileWidth,
		tilePos.y  * Config.tileHeight) + Config.battlefieldOffset;
	if (!this->moving)
	{
		this->sprite.setPosition(pixelPos);
		this->spellEffect.setPosition(pixelPos);
		this->lineHP.setPosition(pixelPos - sf::Vector2f(0,Config.tileHeight));
		this->text.setPosition(pixelPos - sf::Vector2f(0, 60));
	}
	this->pos = tilePos;
	this->pos2.y = tilePos.y;
	if (this->bigCreature)
		this->pos2.x = tilePos.x - 1;
	else
		this->pos2 = tilePos;
}

void BattleUnit::setVelocity(const sf::Vector2i direction)
{
	this->velocity = sf::Vector2f(direction);
	if (abs(velocity.x) == 1 && abs(velocity.y) == 1)
		this->velocity /= 1.41f;
	this->velocity.y *= (Config.tileHeight / Config.tileWidth);
	
}

void BattleUnit::setEnemy(bool enemy)
{
	if(enemy)
		this->lineHP.setFillColor(sf::Color::Red);
	else
		this->lineHP.setFillColor(sf::Color::Green);
	this->enemy = enemy;
}

void BattleUnit::giveOrder(Order order)
{
	this->order = order;
}

void BattleUnit::clickLeft([[maybe_unused]] bool down, [[maybe_unused]] bool previousState)
{
	if (previousState && down == false)
	{
		if (this->keyTime < 0.5)
		{
			this->onDoubleClick();
		}
		else
		{
			this->onClick();
			this->keyTime = 0;
		}
	}
}

void BattleUnit::clickRight(bool down, bool previousState)
{
	if ( down )
	{
		if (this->alive && BH.battlefield->gamePaused && !BH.battlefield->areUnitSelected())
		{
			auto creatureInfo = std::make_shared<CreatureInfo>(
				this->shape.left, this->shape.top, this);
			GH.makePopup(creatureInfo);
		}
	}
}

BattleUnit::BattleUnit(Monster type) :
	InterfaceElem(),
	type(type),
	velocity(sf::Vector2f(0, 0)),
	alive(true),
	enemy(false)
{
	this->initStatistic();
	this->initAnimation2();
	this->animationState = AnimationState::IDLE;
	this->lastDirection = false;
	this->target = nullptr;
	this->order = Order::AGRESIVE_STANCE;
	this->spellToAnimate = Spell::SpellType::NONE;
	this->spellEffect.setColor(sf::Color(255,255,255,0));
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
	this->lineHP.setSize(sf::Vector2f(25.f * this->getSize().x, 3));
	this->text.setFont(GH.globalFont);
	this->text.setCharacterSize(12);
	this->updateNeighbourPos();
	this->fixSpritePos();
	this->thread = false;
}

BattleUnit::~BattleUnit()
{
}

bool BattleUnit::calculatingPaths()
{
	if (this->pathfinderNeedToUpdate)
	{
		this->pathfinderNeedToUpdate = false;
		this->pathfinder->initializeGraph();

		this->pathfinder->calculatePaths();

		return true;
	}
	return false;
}

void BattleUnit::updatePathfinder(const float& dt)
{
	this->timeToUpdatePathfinder += dt * 20.f * (1.f + (std::rand() % 10)/20.f);
	if (this->getAlive() && timeToUpdatePathfinder > 140)
	{
		pathfinderNeedToUpdate = true;
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
		sf::Vector2i temp;
		if (dirs[i].x > 0)
		{
			for (int y = 0; y < getSize().y; y++)
			{
				temp = this->pos + dirs[i] + sf::Vector2i(getSize().x - 1, y);
				if(neighbourTilePos.find(temp) == neighbourTilePos.end())
					neighbourTilePos.insert(temp);
			}
		}
		if (dirs[i].y > 0)
		{
			for (int x = 0; x < getSize().x; x++)
			{
				temp = this->pos + dirs[i] + sf::Vector2i(x, getSize().y - 1);
				if (neighbourTilePos.find(temp) == neighbourTilePos.end())
					neighbourTilePos.insert(temp);
			}
		}
		if (dirs[i].x < 0)
		{
			for (int y = 0; y < getSize().y; y++)
			{
				temp = this->pos + dirs[i] + sf::Vector2i(0, y);
				if (neighbourTilePos.find(temp) == neighbourTilePos.end())
					neighbourTilePos.insert(temp);
			}
		}
		if (dirs[i].y < 0)
		{
			for (int x = 0; x < getSize().x; x++)
			{
				temp = this->pos + dirs[i] + sf::Vector2i(x, 0);
				if (neighbourTilePos.find(temp) == neighbourTilePos.end())
					neighbourTilePos.insert(temp);
			}
		}
	}
}

void BattleUnit::updateSpellAnimation(const float& dt)
{
	if (this->spellToAnimate.spell != Spell::SpellType::NONE)
	{
		if(spellVisible == 0)
			this->spellEffect.setTexture(*graphics2.battleEffects[this->spellToAnimate.spell]);
		this->spellVisible += dt;
	
		auto color = this->spellEffect.getColor();
		
		this->spellEffect.setColor(color);
		if (spellVisible > 3)
		{
			spellVisible = 0;
			this->spellToAnimate.spell = Spell::SpellType::NONE;
		}
		else if(spellVisible > 1.5)
		{
			if (color.a < 20) color.a = 0;
			else color.a -= 20;

		}
		else
		{
			if (color.a > 235) color.a = 255;
			else color.a += 20;
		}

		this->spellEffect.setColor(color);
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

void BattleUnit::updateAnimation2(const float& dt)
{
	std::string action = "IDLE";
	bool playReversly = false;
	switch (this->animationState)
	{
	case AnimationState::IDLE:
		action = "IDLE";
		break;
	case AnimationState::START_MOVING:
		action = "MOVE";
		break;
	case AnimationState::RUNNING:
		action = "RUN";
		break;
	case AnimationState::MOVING: {
		action = "MOVE";
		break;
	}
	case AnimationState::SHOOTHING: {
		if (!this->target)
			break;
		action = "ATTAK";
		if (this->animator->playedHalf(action)
			&& this->actualAttackCoulddown <= 0)
			this->shooted = true;
		break;
	}
	case AnimationState::ATTACKING: {
		if (!this->target)
			break;
		action = "ATTAK";
		if (this->animator->playedHalf(action)
			&& this->actualAttackCoulddown <= 0)
			this->attacked = true;
		break;
	}
	case AnimationState::BLOCKING:
		break;
	case AnimationState::RECIVING_DMG:
		action = "HURT";
		if (this->animator->playedOnce(action))
			this->recivingDamage = false;
		break;
	case AnimationState::DIEING:
		action = "DIE";
		if (this->animator->playedOnce(action))
			this->alive = false;
		break;
	default:
		break;
	}
	//this->text.setString(action);
	
	if (this->moving || this->animationState == AnimationState::IDLE)
		this->animator->play(action, dt, this->lastDirection);
	else if (!this->animator->playedOnce(action))
		this->animator->play(action, dt, this->lastDirection, playReversly);
	else
		this->animationState = AnimationState::IDLE;
	
}

void BattleUnit::update(const float& dt)
{
	if (this->alive && !this->isBlid)
		this->updateAnimation2(dt);
	if (this->isBlid)
		this->updateAnimation2(0);
	this->keyTime = std::min(this->keyTime + std::max(dt,0.02f), 10.f);
	this->updatePathfinder(dt);
	this->calculatingPaths();
	/*
	if (this->spellToAnimate.spell != Spell::SpellType::NONE)
	{
		if (spellEffectAnimation->playedOnce(spellToString[this->spellToAnimate.spell]))
			this->spellToAnimate.spell = Spell::SpellType::NONE;
		else
			spellEffectAnimation->play(spellToString[this->spellToAnimate.spell], dt, false);
	}
	*/
	this->updateSpellAnimation(dt);
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
	if (this->isBlid) toMove = { 0,0 };
	this->sprite.move(toMove);
	this->spellEffect.move(toMove);
	this->lineHP.move(toMove);
	this->text.move(toMove);
	this->offset += (toMove);
	this->shape.left += (toMove.x);
	this->shape.top += (toMove.y);
	rect.setPosition(shape.left, shape.top);
	if (Config.tileWidth < abs(this->offset.x) || Config.tileHeight < abs(this->offset.y))
	{
		this->moving = false;
		//this->moving2 = false;
		if (this->order == Order::DEFENSIVE_POS)
			this->idle();
		this->offset = { 0, 0 };
		setVelocity(sf::Vector2i(0, 0));
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
	this->lineHP.setSize(sf::Vector2f(25 * this->getSize().x * ((float)hp / (float)maxHp), 3));
}

void BattleUnit::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	if (this->shooter && this->missle)
		this->missle->render(target);
	if (this->spellToAnimate.spell != Spell::SpellType::NONE)
		target->draw(this->spellEffect);
	//this->rect.setFillColor(sf::Color(200,200,200,130));
	//target->draw(this->rect);
	target->draw(this->lineHP);
	target->draw(text);
	for (auto text : this->damageTexts)
		target->draw(text.number);
}

Missle::Missle(BattleUnit* unit) :
	speed(600.f),
	startingPos(unit->getPos())
{
	this->shape.setFillColor(sf::Color::Transparent);
	if (unit->getType() == Monster::ELF1)
	{
		this->sprite.setTexture(graphics2.arrow);
		this->sprite.setOrigin((sf::Vector2f)graphics2.arrow.getSize() / 2.f);

	}
	else if (unit->getType() == Monster::ELF3)
	{
		this->sprite.setTexture(graphics2.magicBulet);
		this->sprite.setOrigin((sf::Vector2f)graphics2.magicBulet.getSize() / 2.f);
	}
	else
	{
		this->shape.setFillColor(sf::Color::Yellow);
	}
	
	auto scalar = (2 * Config.tileWidth) / 130.f;
	this->sprite.setScale(scalar, scalar);
	this->shape = sf::RectangleShape(sf::Vector2f(10, 10));
	this->sprite.setPosition(sf::Vector2f(
		unit->getPos().x * Config.tileWidth,
		unit->getPos().y * Config.tileHeight) + Config.battlefieldOffset);
	this->shape.setPosition(sf::Vector2f(
		unit->getPos().x * Config.tileWidth,
		unit->getPos().y * Config.tileHeight) + Config.battlefieldOffset);
	this->velocity = { 0.f, 0.f };
}

Missle::~Missle()
{
}

void Missle::setTarget(BattleUnit* target)
{
	sf::Vector2i dir = target->getPos() - this->startingPos;
	auto tempp = sf::Vector2f(
		Config.tileWidth * ((float)dir.x + (((float)target->getSize().x / 2.f))),
		Config.tileHeight * ((float)dir.y + (((float)target->getSize().y / 2.f))));
	if(dir.x < 0) this->sprite.setRotation(180);
	float temp;
	if (std::abs(tempp.x) > std::abs(tempp.y))
		temp = 1.f / tempp.x;
	else
		temp = 1.f / tempp.y;
	this->velocity.x = tempp.x * std::abs(temp);
	this->velocity.y = tempp.y * std::abs(temp);

}

sf::Vector2i Missle::getTilePos() const
{

	return sf::Vector2i(
		(int)((this->shape.getPosition().x - Config.battlefieldOffset.x) / Config.tileWidth),
		(int)((this->shape.getPosition().y - Config.battlefieldOffset.y) / Config.tileHeight));
}

void Missle::update(const float& dt)
{
	this->sprite.move(this->velocity * speed * dt);
	this->shape.move(this->velocity * speed * dt);
}

void Missle::render(sf::RenderTarget* target)
{
	//target->draw(this->shape);
	target->draw(this->sprite);
}

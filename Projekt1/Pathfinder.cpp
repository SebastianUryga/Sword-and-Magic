#include "pch.h"
#include "Pathfinder.h"
#include "World.h"

Pathfinder::Pathfinder(sf::Vector2i size, HeroInstance * hero)
	: hero(hero)
{
	nodes.resize(size.y);
	for (auto &i : nodes)
		i.resize(size.x);
}


Pathfinder::~Pathfinder()
{
}

std::vector<PathNode*> Pathfinder::calculateNeighbours(const PathNode * source)
{
	std::vector<PathNode *> neighbours;
	neighbours.reserve(16);
	
	std::vector<sf::Vector2i> accessibleNeighbourTiles;
	accessibleNeighbourTiles.reserve(16);
	this->getNeighbours(source->coord, accessibleNeighbourTiles);

	for (auto & neighbour : accessibleNeighbourTiles)
	{
		auto node = this->getNode(neighbour);
		if (node->accessible == PathNode::NOT_SET)
			continue;

		if (node->accessible == PathNode::BLOCKVIS  || 
			node->accessible == PathNode::VISITABLE ||
			source->accessible == PathNode::VISITABLE)
		{
			if(!world.canMoveBetween(source->coord, node->coord))
				continue;
		}
		neighbours.push_back(node);
	}
	
	
	return neighbours;
}

void Pathfinder::calculatePaths()
{
	PathNode * initialNode = this->getInitialNode();

	push(initialNode);

	while (!pq.empty())
	{
		auto source = this->topAndPop();
		source->locked = true;
		int movement = source->moveRemains;
		uint8_t turn = source->turns;
		float cost = source->getCost();

		auto neighbourNodes = calculateNeighbours(source);
		for (PathNode * neighbour : neighbourNodes)
		{
			if (neighbour->locked)
				continue;
			
			//destination->guarded = isDestinationGuarded();
			this->movementCostRule(source,neighbour);
			if(neighbour->accessible == PathNode::ACCESSIBLE)
				push(neighbour);
		}
	}
}

void Pathfinder::push(PathNode * node)
{
	if (node && !node->inPQ)
	{
		node->inPQ = true;
		pq.push(node);
	}
}

PathNode * Pathfinder::getInitialNode()
{
	auto initialNode = this->getNode(hero->getVisitablePos());

	initialNode->turns = 0;
	initialNode->moveRemains = hero->movement;
	initialNode->setCost(0.0);

	return initialNode;
}

bool Pathfinder::getPath(Path & out, const sf::Vector2i & dst) const
{
	out.nodes.clear();
	auto curnode  = &(this->nodes[dst.y][dst.x]); // nie wiem czemu nie moze byc
	if (!curnode->theNodeBefore || curnode->accessible == PathNode::BLOCKED)				// this->getNode(dst);
		return false;

	while (curnode)
	{
		const PathNode cpn = *curnode;
		curnode = curnode->theNodeBefore;
		out.nodes.push_back(cpn);
	}
	return true;
}

PathNode * Pathfinder::topAndPop()
{
	auto node = pq.top();

	pq.pop();
	node->inPQ = false;
	return node;
}

void Pathfinder::movementCostRule(PathNode * src, PathNode * dst)
{
	int cost = this->getMovementCost(src->coord, dst->coord);
	int remains = src->moveRemains - cost;

	float costAtNextTile = src->getCost() + static_cast<float>(cost);
	int moveAtNextTile = remains;
	int turnAtNextTile = src->turns;
	int maxMovePoints = hero->getMaxMovePoints();

	if (remains < 0)
	{
		++turnAtNextTile;
		moveAtNextTile += maxMovePoints;
	}
	
	//  node haven't checked before or there is better way
	if ((dst->turns == 0xff && src->turns == turnAtNextTile && remains) || dst->getCost() > costAtNextTile)
	{
		dst->setCost(costAtNextTile);
		dst->turns = turnAtNextTile;
		dst->moveRemains = moveAtNextTile;
		dst->theNodeBefore = src;
		return;
	}

	/*
	int turnAtNextTile = destination.turn;
	
	int cost = pathfinderHelper->getMovementCost(source, destination, moveAtNextTile);
	int remains = moveAtNextTile - cost;
	int maxMovePoints = pathfinderHelper->getMaxMovePoints(destination.node->layer);
	if (remains < 0)
	{
		//occurs rarely, when hero with low movepoints tries to leave the road
		costAtNextTile += static_cast<float>(moveAtNextTile) / maxMovePoints;//we spent all points of current turn
		pathfinderHelper->updateTurnInfo(++turnAtNextTile);

		maxMovePoints = pathfinderHelper->getMaxMovePoints(destination.node->layer);
		moveAtNextTile = maxMovePoints;

		cost = pathfinderHelper->getMovementCost(source, destination, moveAtNextTile); //cost must be updated, movement points changed :(
		remains = moveAtNextTile - cost;
	}


	destination.blocked = true;*/
}

int Pathfinder::getMovementCost(const sf::Vector2i & src, const sf::Vector2i & dst)
{
	if (src == dst) //same tile
		return 0;
	const Maps::Tile & t1 = world.GetTile(src.x, src.y);
	const Maps::Tile & t2 = world.GetTile(dst.x, dst.y);
	int ret = hero->getTileCost(t2, t1);

	if (src.x != dst.x && src.y != dst.y) //it's diagonal move
	{
		int old = ret;
		ret *= 1.41421;
		//diagonal move costs too much but normal move is possible - allow diagonal move for remaining move points
		/*if (ret > remainingMovePoints && remainingMovePoints >= old)
		{
			return remainingMovePoints;
		}*/
	}
	return ret;
}

PathNode::Accessibility Pathfinder::evaluateAccessibility(const sf::Vector2i & pos, const Maps::Tile * tinfo, const int player)
{
	if (tinfo->isFog(player))
		return PathNode::BLOCKED;

	if (tinfo->GetObjectPtr() && tinfo->isVisitable())
	{
		/*if (tinfo->visitableObjects.front()->ID == Obj::SANCTUARY && tinfo->visitableObjects.back()->ID == Obj::HERO && tinfo->visitableObjects.back()->tempOwner != player) //non-owned hero stands on Sanctuary
		{
			return PathNode::BLOCKED;
		}
		else*/
		//{
		const MP2::ObjectInstance * obj = tinfo->objects.front();
		if (obj->blockVisit)
			return PathNode::BLOCKVIS;
		else
			return PathNode::VISITABLE;
		/*else if (obj->passableFor(player))
			return PathNode::ACCESSIBLE;
		else if (obj->ID != Obj::EVENT)
			return CGPathNode::VISITABLE;*/
		//}
	}
	else if (tinfo->isBlocked())
	{
		return PathNode::BLOCKED;
	}
	/*else if (world->guardingCreaturePosition(pos).valid())
	{
		// Monster close by; blocked visit for battle
		return PathNode::BLOCKVIS;
	}*/

	return PathNode::ACCESSIBLE;
}


void Pathfinder::initializeGraph()
{
	sf::Vector2i pos;
	const sf::Vector2i sizes(world.w(), world.h());
	const int player = this->hero->getOwner();
	for (pos.x = 0; pos.x < sizes.x; ++pos.x)
	{
		for (pos.y = 0; pos.y < sizes.y; ++pos.y)
		{
			Maps::Tile * tile = &world.GetTile(pos.x, pos.y);
			this->getNode(pos)->reset();
			this->getNode(pos)->update(pos, this->evaluateAccessibility(pos, tile, player));
		}
		
	}
}

void Pathfinder::resetGraph()
{
	for (auto i : nodes)
		for (auto& j : i)
		{
			j.reset();
		}
			
}

void Pathfinder::getNeighbours(const sf::Vector2i & src, std::vector<sf::Vector2i>& vec)
{
	static const sf::Vector2i dirs[] = {
		sf::Vector2i(-1, +1), sf::Vector2i(0, +1), sf::Vector2i(+1, +1),
		sf::Vector2i(-1, +0),   /* source pos */   sf::Vector2i(+1, +0),
		sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(+1, -1)
	};
	for (auto & dir : dirs)
	{
		const sf::Vector2i hlp = src + dir;
		if (!world.isInTheMap(hlp))
			continue;

		const Maps::Tile& tile = world.GetTile(hlp.x, hlp.y);
		if (tile.GetGround() == Maps::Ground::WATER)
			continue;


		vec.push_back(hlp);
	}
}

sf::Vector2i  Path::startPos() const
{
	return nodes[nodes.size() - 1].coord;
}

sf::Vector2i Path::endPos() const
{
	return nodes[0].coord;
}

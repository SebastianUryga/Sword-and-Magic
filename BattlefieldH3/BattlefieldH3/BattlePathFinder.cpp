#include "GuiHandler.h"

Battle::PathFinder::PathFinder(Battlefield* map, BattleUnit* unit)
	:battlefield(map), unit(unit)
{
	auto size = this->battlefield->getSize();
	this->nodes.resize(size.x);
	for (auto& node : this->nodes)
		node.resize(size.y);

}

Battle::PathFinder::~PathFinder()
{
}

void Battle::PathFinder::initializeGraph()
{
	sf::Vector2i pos;
	const sf::Vector2i sizes = this->battlefield->getSize();
	for (pos.x = 0; pos.x < sizes.x; ++pos.x)
	{
		for (pos.y = 0; pos.y < sizes.y; ++pos.y)
		{
			auto tile = this->battlefield->getTile(pos);
			this->getNode(pos)->reset();
			this->getNode(pos)->coord = pos;
			this->getNode(pos)->accessible = this->evaluateAccessibility(tile);
		}

	}
}

void Battle::PathFinder::resetGraph()
{
	for (auto i : nodes)
		for (auto& j : i)
		{
			j.reset();
		}
}

bool Battle::PathFinder::getPath(Battle::BPath& out, const sf::Vector2i& dst) const
{
	out.nodes.clear();
	auto curnode = &(this->nodes[dst.x][dst.y]); // nie wiem czemu nie moze byc
	if (!curnode->theNodeBefore || curnode->accessible == PathNode::Accessibility::BLOCKED)	// this->getNode(dst);
		return false;

	while (curnode)
	{
		const Battle::PathNode cpn = *curnode;
		curnode = curnode->theNodeBefore;
		out.nodes.push_back(cpn);
	}
	return true;
}

void Battle::PathFinder::calculatePaths()
{
	Battle::PathNode* initialNode = this->getInitialNode();
	bool bigCreature = unit->isBig();

	this->push(initialNode);

	while (!this->pq.empty())
	{
		auto source = this->topAndPop();
		source->locked = true;
		float cost = source->getCost();

		auto neighbourNodes = calculateNeighbours(source);
		for (PathNode* neighbour : neighbourNodes)
		{
			if (neighbour->locked)
				continue;

			auto destination = neighbour;
			float cost = this->getMovementCost(source->coord, destination->coord);
			float costAtNextTile = source->getCost() + static_cast<float>(cost);
			if (destination->getCost() > costAtNextTile)
			{
				destination->setCost(costAtNextTile);
				destination->theNodeBefore = source;
			}
			auto pos2 = neighbour->coord - sf::Vector2i(bigCreature, 0);
			
			if (!battlefield->containsIsBattlefield(pos2))
				continue;
			auto neighbour2 = this->getNode(pos2);
			
			if ((destination->coord == source->coord - sf::Vector2i(bigCreature, 0) || neighbour->accessible == PathNode::Accessibility::ACCESSIBLE) &&
				(pos2 == source->coord || neighbour2->accessible == PathNode::Accessibility::ACCESSIBLE))
				push(neighbour);
		}
	}
}

Battle::PathNode::Accessibility Battle::PathFinder::evaluateAccessibility(const BattleTile& tinfo)
{
	if (tinfo.unit && tinfo.blocked)
		return PathNode::Accessibility::BLOCKVIS;
	if (tinfo.blocked)
		return PathNode::Accessibility::BLOCKED;
	return PathNode::Accessibility::ACCESSIBLE;
}

std::vector<Battle::PathNode*> Battle::PathFinder::calculateNeighbours(const PathNode* source)
{
	std::vector<PathNode*> neighbours;
	neighbours.reserve(16);

	static const sf::Vector2i dirs[] = {
		sf::Vector2i(-1, +1), sf::Vector2i(0, +1), sf::Vector2i(+1, +1),
		sf::Vector2i(-1, +0),   /* source pos */   sf::Vector2i(+1, +0),
		sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(+1, -1)
	};
	for (auto& dir : dirs)
	{
		const sf::Vector2i hlp = source->coord + dir;
		if (!this->battlefield->containsIsBattlefield(hlp))
			continue;

		auto node = this->getNode(hlp);
		if (node->accessible == PathNode::Accessibility::NOT_SET)
			continue;
		neighbours.push_back(node);
	}

	return neighbours;
}

float Battle::PathFinder::getMovementCost(const sf::Vector2i& src, const sf::Vector2i& dst)
{
	if (src == dst) //same tile
		return 0;
	float ret = 100;
	if (src.x != dst.x && src.y != dst.y) //it's diagonal move
		ret *= 1.41;
	return ret;
}

Battle::PathNode* Battle::PathFinder::topAndPop()
{
	auto node = pq.top();

	pq.pop();
	node->inPQ = false;
	return node;
}

void Battle::PathFinder::push(PathNode* node)
{
	if (node && !node->inPQ)
	{
		node->inPQ = true;
		pq.push(node);
	}
}

Battle::PathNode* Battle::PathFinder::getInitialNode(bool bigCreature)
{
	sf::Vector2i pos;
	if (bigCreature)
		pos = this->unit->getPos2();
	else
		pos = this->unit->getPos();
	auto initialNode = this->getNode(pos);
	initialNode->setCost(0.0);

	return initialNode;
}

Battle::PathNode::PathNode()
{
	this->reset();
}

Battle::PathNode::~PathNode()
{
}

sf::Vector2i Battle::BPath::startPos() const
{
	return nodes[nodes.size() - 1].coord;
}

sf::Vector2i Battle::BPath::nextPos() const
{
	if (nodes.size() > 1)
		return nodes[nodes.size() - 2].coord;
	return sf::Vector2i(-1, -1);
}

sf::Vector2i Battle::BPath::endPos() const
{
	return nodes[0].coord;
}

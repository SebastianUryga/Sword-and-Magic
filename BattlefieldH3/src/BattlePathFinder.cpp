#include "BattlePathFinder.h"
#include "Battlefiled.h"

Battle::PathFinder::PathFinder(Battlefield* map, BattleUnit* unit) :
	unit(unit),
	battlefield(map)
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
			const auto tile = this->battlefield->getTile(pos);
			auto node = this->getNode(pos);
			node->reset();
			node->coord = pos;
			node->accessible = this->evaluateAccessibility(tile);
			
		}
	}
	for (auto& node : this->nodes)
		for (auto& n : node)
			if (n.neighbourNodes.empty())
				calculateNeighbours(&n, n.neighbourNodes);
}

void Battle::PathFinder::resetGraph()
{
	for (auto i : nodes)
		for (auto& j : i)
		{
			j.reset();
		}
}

bool Battle::PathFinder::getPath(Battle::BPath& out, const sf::Vector2i& dst)
{
	if (!this->battlefield->containsIsBattlefield(dst)) return false;

	out.nodes.clear();
	auto curnode = &(this->nodes[dst.x][dst.y]);		// nie wiem czemu nie moze byc

	if (curnode->theNodeBefore[0] == nullptr ) // this->getNode(dst);
		return false;

	while (curnode != nullptr)
	{
		const Battle::PathNode cpn = *curnode;
		if (curnode->theNodeBefore[0] && !this->battlefield->isTileBlocked(curnode->theNodeBefore[0]->coord))
			curnode = curnode->theNodeBefore[0];
		else if (curnode->theNodeBefore[1] && !this->battlefield->isTileBlocked(curnode->theNodeBefore[1]->coord))
			curnode = curnode->theNodeBefore[1];
		else if (curnode->theNodeBefore[2] && !this->battlefield->isTileBlocked(curnode->theNodeBefore[2]->coord))
			curnode = curnode->theNodeBefore[2];
		else
			curnode = curnode->theNodeBefore[0];

		out.nodes.push_back(cpn);
	}
	return true;
}

void Battle::PathFinder::calculatePaths()
{
	Battle::PathNode* initialNode = this->getInitialNode();
	bool bigCreature = unit->isBig();
	//static std::vector<Battle::PathNode*> neighbourNodes;

	this->push(initialNode);
	sf::Clock clock;
	clock.restart();
	float sec = 0;

	while (!this->pq.empty())
	{
		auto source = this->topAndPop();
		//if (clock.getElapsedTime().asMilliseconds() > 15) while (!this->pq.empty()) this->pq.pop();

		source->locked = true;

		//this->calculateNeighbours(source, neighbourNodes);
		for (PathNode* neighbour : source->neighbourNodes)
		{
			if (neighbour->locked)
				continue;

			auto destination = neighbour;
			
			bool available = true;

			clock.restart();
			if (source->coord.x < destination->coord.x)
			{
				for (int y = 0; y < unit->getSize().y; y++)
				{
					auto tile = destination->coord + sf::Vector2i(unit->getSize().x - 1, y);
					available &= this->checkTileAvailable(tile);
				}
					
			}
			if (source->coord.y < destination->coord.y)
			{
				for (int x = 0; x < unit->getSize().x; x++)
				{
					auto tile = destination->coord + sf::Vector2i(x, unit->getSize().y - 1);
					available &= this->checkTileAvailable(tile);
				}
			}
			if (source->coord.x > destination->coord.x)
			{
				for (int y = 0; y < unit->getSize().y; y++)
				{
					auto tile = destination->coord + sf::Vector2i(0, y);
					available &= this->checkTileAvailable(tile);
				}
			}
			if (source->coord.y > destination->coord.y)
			{
				for (int x = 0; x < unit->getSize().x; x++)
				{
					auto tile = destination->coord + sf::Vector2i(x, 0);
					available &= this->checkTileAvailable(tile);
				}
			}
			sec += clock.restart().asMicroseconds();
			float cost = this->getMovementCost(source->coord, destination->coord);
			float costAtNextTile = source->getCost() + static_cast<float>(cost);


			if (destination->getCost() >= costAtNextTile)
			{
				destination->setCost(costAtNextTile);
				destination->theNodeBefore[2] = destination->theNodeBefore[1];
				destination->theNodeBefore[1] = destination->theNodeBefore[0];
				destination->theNodeBefore[0] = source;
			}

			if (available)
				push(neighbour);
		}
	}
	//std::cout << " path finder time" << clock.getElapsedTime().asMilliseconds() << std::endl;
	std::cout << " path finder time" <<sec << std::endl;
}

Battle::PathNode::Accessibility Battle::PathFinder::evaluateAccessibility(const BattleTile& tinfo)
{
	if (tinfo.unit == this->unit)
		return PathNode::Accessibility::ACCESSIBLE;
	if (tinfo.unit && tinfo.blocked)
		return PathNode::Accessibility::BLOCKVIS;
	if (tinfo.blocked)
		return PathNode::Accessibility::BLOCKED;
	return PathNode::Accessibility::ACCESSIBLE;
}

void Battle::PathFinder::calculateNeighbours(const PathNode* source, std::vector<PathNode*>& resultNodes)
{
	resultNodes.clear();
	resultNodes.reserve(9);
	static const sf::Vector2i dirs[] = {
		sf::Vector2i(-1, +1), sf::Vector2i(0, +1), sf::Vector2i(+1, +1), sf::Vector2i(-1, +0), /* source pos */ sf::Vector2i(+1, +0), sf::Vector2i(-1, -1), sf::Vector2i(0, -1), sf::Vector2i(+1, -1)
	};
	
	for (auto& dir : dirs)
	{
		const sf::Vector2i hlp = source->coord + dir;
		if (!this->battlefield->containsIsBattlefield(hlp))
			continue;

		auto node = this->getNode(hlp);
		if (node->accessible == PathNode::Accessibility::NOT_SET)
			continue;
		resultNodes.push_back(node);
	}

}

float Battle::PathFinder::getMovementCost(sf::Vector2i src, sf::Vector2i dst)
{
	if (src == dst) //same tile
		return 0;
	float ret = 100;
	if (src.x != dst.x && src.y != dst.y) //it's diagonal move
		ret *= 1.41;
	return ret;
}

bool Battle::PathFinder::checkTileAvailable(sf::Vector2i tile)
{
	if (!battlefield->containsIsBattlefield(tile))
	{
		return false;
	}
	auto node = this->getNode(tile);
	if (node->accessible == PathNode::Accessibility::BLOCKED)
	{
		return false;
	}
	if (node->accessible == PathNode::Accessibility::BLOCKVIS)
	{
		return false;
	}
	return true;
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

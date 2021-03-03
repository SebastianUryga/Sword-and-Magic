#pragma once
#include "GameConstants.h"

class HeroInstance;
namespace Maps
{
	class Tile;
}

template<typename N>
struct NodeComparer
{
	bool operator()(const N * lhs, const N * rhs) const
	{
		return lhs->getCost() > rhs->getCost();
	}
};

class PathNode
{
public:
	enum ENodeAction : uint8_t
	{
		UNKNOWN = 0,
		EMBARK = 1,
		DISEMBARK,
		NORMAL,
		BATTLE,
		VISIT,
		BLOCKING_VISIT,
	};
	enum Accessibility : uint8_t
	{
		NOT_SET = 0,
		ACCESSIBLE = 1, //tile can be entered and passed
		VISITABLE, //tile can be entered as the last tile in path
		BLOCKVIS,  //visitable from neighboring tile but not passable
		FLYABLE, //can only be accessed in air layer
		BLOCKED //tile can't be entered nor visited
	};
	sf::Vector2i coord;
	uint8_t turns;
	Accessibility accessible;
	PathNode * theNodeBefore;
	int moveRemains;
	bool inPQ;
	bool locked;

	float getCost() const { return this->cost; }
	void setCost(float value)
	{
		if (value == this->cost)
			return;

		bool getUpNode = value < this->cost;
		this->cost = value;
		// If the node is in the heap, update the heap.
		if (this->inPQ)
		{
			this->inPQ = false;
		}
	}
	void reset()
	{
		this->locked = false;
		this->accessible = NOT_SET;
		this->moveRemains = 0;
		this->cost = std::numeric_limits<float>::max();
		this->turns = 255;
		this->theNodeBefore = nullptr;
		this->inPQ = false;
		//pq = nullptr;
	}
	void update(const sf::Vector2i & Coord, const Accessibility Accessible)
	{
		this->coord = Coord;
		this->accessible = Accessible;
	}
	float cost; //total cost of the path to this tile measured in turns with fractions
};

struct Path
{
	std::vector<PathNode> nodes; //just get node by node

	sf::Vector2i startPos() const; // start point
	sf::Vector2i endPos() const; //destination point
};

class Pathfinder
{
public:
	const HeroInstance * hero;
	std::priority_queue<PathNode*, std::vector<PathNode*>, NodeComparer<PathNode>> pq;
	std::vector<std::vector<PathNode>> nodes;

	Pathfinder(sf::Vector2i size, HeroInstance * hero);
	virtual ~Pathfinder();

	std::vector<PathNode *> calculateNeighbours(
		const PathNode * source);

	void calculatePaths();
	void push(PathNode * node);
	PathNode * getInitialNode();
	PathNode * getNode(const sf::Vector2i & coord)
	{
		return &nodes[coord.y][coord.x];
	}

	bool getPath(Path & out, const sf::Vector2i & dst) const;
	PathNode * topAndPop();
	void movementCostRule(PathNode* src, PathNode * dst);
	int getMovementCost(const sf::Vector2i & src, const sf::Vector2i & dst);
	PathNode::Accessibility evaluateAccessibility(const sf::Vector2i & pos, const Maps::Tile * tinfo, const int player);
	void initializeGraph();
	void resetGraph();
	void getNeighbours(const sf::Vector2i & tile,
		std::vector<sf::Vector2i> & vec);
};


#pragma once

class Battlefield;
class BattleUnit;
struct BattleTile;

namespace Battle
{

	template<typename N>
	struct NodeComparer
	{
		bool operator()(const N* lhs, const N* rhs) const
		{
			return lhs->getCost() > rhs->getCost();
		}
	};

	class PathNode
	{
	private:
		float cost;
	public:
		enum class Accessibility : uint8_t
		{
			NOT_SET = 0,
			ACCESSIBLE = 1, //tile can be entered and passed
			BLOCKVIS,  //visitable from neighboring tile but not passable
			BLOCKED //tile can't be entered nor visited
		};
		PathNode();
		virtual ~PathNode();
		float getCost() const
		{
			return this->cost;
		}

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
			this->accessible = Accessibility::NOT_SET;
			this->cost = std::numeric_limits<float>::max();
			this->theNodeBefore = nullptr;
			this->inPQ = false;
		}
		sf::Vector2i coord;
		Accessibility accessible;
		PathNode* theNodeBefore;
		bool inPQ;
		bool locked;
	};

	struct BPath
	{
		std::vector<PathNode> nodes; //just get node by node

		sf::Vector2i startPos() const; // start point
		sf::Vector2i nextPos() const;
		sf::Vector2i endPos() const; //destination point
	};

	class PathFinder
	{
	public:
		const BattleUnit* unit;

		PathFinder(Battlefield* map, BattleUnit* unit);
		virtual ~PathFinder();

		//functions
		void initializeGraph();
		void resetGraph();
		bool getPath(BPath& out, const sf::Vector2i& dst) const;
		void calculatePaths();

		PathNode* getNode(const sf::Vector2i& coord)
		{
			return &nodes[coord.x][coord.y];
		}
	private:
		//variables
		const Battlefield* battlefield;
		std::priority_queue<PathNode*, std::vector<PathNode*>, NodeComparer<PathNode>> pq;
		std::vector<std::vector<PathNode>> nodes;

		//functions
		PathNode::Accessibility evaluateAccessibility(const BattleTile& tinfo);
		std::vector<PathNode*> calculateNeighbours(const PathNode* source);
		float getMovementCost(const sf::Vector2i& src, const sf::Vector2i& dst);
		PathNode* getInitialNode(bool bigCreature = false);
		PathNode* topAndPop();
		void push(PathNode* node);

	};

}
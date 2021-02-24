#pragma once
struct Path;
class PathNode;

enum movment_state 
{
	IDLE = 0, MOVING_UP, MOVING_RIGHT, MOVING_DOWN, MOVING_LEFT,
	MOVING_UP_RIGHT, MOVING_UP_LEFT, MOVING_DOWN_RIGHT, MOVING_DOWN_LEFT
};

class MovmentComponent
{
private:
	sf::Sprite& sprite;
	sf::Vector2i tilePos;

	float speed;
	sf::Vector2f offset;

	sf::Vector2f velocity;
	bool moving;
	int nodeIndex;
	bool positionChanged;
	bool pathEnded;
	std::shared_ptr<Path> path;
	//Initializer Functions

public:
	MovmentComponent(sf::Sprite& sprite);
	virtual ~MovmentComponent();

	void setTexture(sf::Texture& texture); 

	const sf::Vector2f& getVelocity() const;

	//Functions
	const bool getState(const short unsigned state) const;
	bool isHeroChangedPos();
	bool isPathEnded();
	bool setNewPath(std::shared_ptr<Path> path);
	sf::Vector2i getActualHeroTilePos();

	void DoMove(int x, int y);
	void StartMoving();
	void stopMoving();

	virtual void update(const float& dt);
};


#pragma once
class BorderWindow
{
protected:
	
	sf::RectangleShape background;
public:
	BorderWindow(float x, float y, float width, float height);
	virtual ~BorderWindow();

	//Functions

	virtual void setPos(float x, float y) = 0;

	virtual void update(sf::Vector2i mousePosWindow) = 0;
	virtual void render(sf::RenderTarget *target) = 0;
};


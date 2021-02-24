#pragma once
#include "WindowObject.h"
#include "HeroInstance.h"
class GuiHandler;

class HeroWindow  : public WindowObject
{
private:

	sf::Text name;
	sf::Sprite portraitImage;
	void initBackground();
	void initButtons();
public:
	const HeroInstance * curHero;
	HeroWindow(const HeroInstance * hero);
	virtual ~HeroWindow();

	void dismissCurrent();
	// Functions
	void setPos(float x, float y);
	void update(const float dt,const sf::Vector2i mousePos) override;
	void render(sf::RenderTarget * target) override;
};


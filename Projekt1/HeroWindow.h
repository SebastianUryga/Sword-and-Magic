#pragma once
#include "WindowObject.h"
#include "HeroInstance.h"
#include "GarrnisonInterface.h"

class GuiHandler;

class HeroWindow  : public WindowObject
{
private:

	sf::Sprite portraitImage;
	std::shared_ptr<GarrnisonInterface> gar;
	void initGarrison(std::vector<Troop>& troops);
	void initBackground();
	void initButtons();
public:
	HeroInstance * curHero;
	HeroWindow(HeroInstance * hero);
	virtual ~HeroWindow();

	void dismissCurrent();
	// Functions
	void setPos(float x, float y);
	void update(const float dt,const sf::Vector2i mousePos) override;
	void render(sf::RenderTarget * target) override;
};


#pragma once
#include "WindowObject.h"
#include "HeroInstance.h"
class GuiHandler;

class HeroWindow  : public WindowObject
{
private:
	
	std::map<std::string, std::shared_ptr<Button>> buttons;

	sf::Text name;
	sf::Sprite portraitImage;
	void initBackground();
	void initButtons();
public:
	const HeroInstance * curHero;
	HeroWindow(const HeroInstance * hero);
	virtual ~HeroWindow();

	// Functions
	void setPos(int x, int y);
	//void OnMouseLeftButtonClick() override;
	void updateButtons(const sf::Vector2i mousePos);
	void update(const sf::Vector2i mousePos) override;
	void render(sf::RenderTarget * target) override;
};


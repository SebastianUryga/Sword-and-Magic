#pragma once
#include"IntObject.h"

class GarrnisonInterface;
class HeroInstance;
struct Troop;

class GarrnisonSlot : public IntObject
{
public:
	Troop* stack;
	sf::Sprite sprite;
	sf::Text number;
	sf::RectangleShape selectFrame;
	void setPos(sf::Vector2f pos);
	void setTroop(Troop* troop);
	void clickLeft(bool down, bool previousState) override;
	void clickRight(bool down, bool previousState) override;
	GarrnisonSlot(GarrnisonInterface* owner, int id, float x, float y);
	virtual ~GarrnisonSlot() {}
	int id;
private:
	GarrnisonInterface* owner;
};

class GarrnisonInterface
{
public:
	GarrnisonSlot* selected;
	GarrnisonSlot* getSelected();
	void selectSlot(GarrnisonSlot * slot);

	std::vector<std::shared_ptr<GarrnisonSlot>> slots;
	std::vector<Troop>& garrnison;

	GarrnisonInterface(std::vector<Troop>& troops, sf::Vector2f pos);
	virtual ~GarrnisonInterface();

	void render(sf::RenderTarget* target);
	void updateSlots();
private:
};


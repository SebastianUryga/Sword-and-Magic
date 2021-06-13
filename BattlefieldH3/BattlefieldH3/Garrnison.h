#pragma once
class GarrnisonSlot;

struct Troop
{
	Monster monster;
	int count;
};

class Garrnison
{
public:
	GarrnisonSlot* selected;
	GarrnisonSlot* getSelected();
	void selectSlot(GarrnisonSlot* slot);
	void mergeStacks(int stack1Id, int stack2Id); // Mergeing to stack1
	void swapStacks(int stack1Id, int stack2Id);

	std::vector<std::shared_ptr<GarrnisonSlot>> slots;
	std::vector<Troop>& garrnison;

	Garrnison(std::vector<Troop>& troops, sf::Vector2f pos);
	virtual ~Garrnison();

	void render(sf::RenderTarget* target);
	void updateSlots();
private:
};

class GarrnisonSlot : public InterfaceElem
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
	GarrnisonSlot(Garrnison* owner, int id, float x, float y);
	virtual ~GarrnisonSlot() {}
	int id;
private:
	Garrnison* owner;
};

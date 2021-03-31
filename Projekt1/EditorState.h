#pragma once
#include"GameState.h"


class EditorState :
	public State
{
private:
	enum Mode
	{
		Erase,
		PutObject,
		ChangePos,
		ChangeGround,
		MakeRoads
	};
	Mode mode;
	std::map<std::string, Button*> buttons;
	sf::View view;

	MP2::ObjectInstance* selection;

	int chosenTypeObj;
	int chosenRoadType;
	bool settingRoad;

	void initView();
	void initBackground();
	void initKeybinds();
	void initWorld();
	void initButtons();
	void initGameArea();
public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	void OnMouseLeftButtonClick() override;
	void OnMouseLeftButtonReleased() override;
	
	// Functions
	void endState() override;

	void updateRoadSettingMode();
	void updateSelectObj();
	void updateButtons();
	void updateView();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};


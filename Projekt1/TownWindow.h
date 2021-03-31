#pragma once
#include "WindowObject.h"
#include "TownInstance.h"

class GuiHandler;
class TownInstance;

class TownWindow :
	public WindowObject
{
public:
	TownInstance * curTown;

	void initButtons();

	void showListOfAvaibleBuildings(int slot);
	TownWindow(TownInstance* twon);
	virtual ~TownWindow();
};

class BuildingsList
	: public WindowObject
{
public:

	std::vector<BuildingID> avaibleBuildingList;
	BuildingsList(std::vector<BuildingID> list, int slot);
	void addButton(std::shared_ptr<Button> btn);
	void build(BuildingID building);
private:
	int slot;
};

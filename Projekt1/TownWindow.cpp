#include "pch.h"
#include "TownWindow.h"
#include "GuiHandler.h"

void TownWindow::showListOfAvaibleBuildings(int slot)
{
	std::vector<BuildingID> avaible;

	avaible.push_back(TAVERN);
	avaible.push_back(GUARDHOUSE);
	avaible.push_back(ARCHER_TOWER);
	avaible.push_back(GRIFFIN_TOWER);
	avaible.push_back(BARACKS);
	std::shared_ptr<BuildingsList> window;
	window = std::make_shared<BuildingsList>(avaible, slot);

	std::shared_ptr<Button> builtButton;

	bool isTavernBuild = false;
	for (auto building : this->curTown->buldings)
		if (building->id == TAVERN)
			isTavernBuild = true;

	//  adding build buttons to BuildList and setting them
	for (auto id : avaible)
	{
		builtButton = std::make_shared<Button>(
			0, 0, 40, 30, &this->font, "Build");
		if (id == TAVERN && isTavernBuild)
			builtButton->block(true);

		if (buildingStats[id].cost > world.GetKingdom(PI->getCurrentColor()).getMoney())
			builtButton->block(true);

		builtButton->addFuctionallity([=]()
		{
			PI->bulid(id, slot);
			window->close();
			this->initButtons();
		});

		//builtButton->addRightClickPopup();
		window->addButton(builtButton);
	}
	GH.pushWindow(window);
	
}

TownWindow::TownWindow(TownInstance* twon)
	: WindowObject(200, 100, 600, 400, GH.globalFont),curTown(twon)
{
	this->initButtons();
}


void TownWindow::initButtons()
{
	this->interactiveElem.clear();
	for (int i = 0; i < 6; i++)
	{
		std::string temp = "";
		if (curTown->buldings[i]->id == NONE)
			temp = "Slot" + std::to_string(i+1);
		else
			temp = curTown->buldings[i]->name;
		this->buttons["Slot" + std::to_string(i+1)] = std::make_shared<Button>(
			this->background.getPosition().x + 30,
			this->background.getPosition().y + 50,
			100, 30, &this->font, temp
			);
	}
	this->buttons["Slot1"]->setPos(
		this->background.getPosition().x + 30,
		this->background.getPosition().y + 50);
	this->buttons["Slot2"]->setPos(
		this->background.getPosition().x + 30,
		this->background.getPosition().y + 130);
	this->buttons["Slot3"]->setPos(
		this->background.getPosition().x + 150,
		this->background.getPosition().y + 130);
	this->buttons["Slot4"]->setPos(
		this->background.getPosition().x + 280,
		this->background.getPosition().y + 130);
	this->buttons["Slot5"]->setPos(
		this->background.getPosition().x + 410,
		this->background.getPosition().y + 50);
	this->buttons["Slot6"]->setPos(
		this->background.getPosition().x + 410,
		this->background.getPosition().y + 130);

	for (int i = 0; i < curTown->buldings.size(); i++)
	{
		std::function<void()> fun = [=]() {
			if (curTown->buldings[i]->id == NONE)
				this->showListOfAvaibleBuildings(i);
			if (curTown->buldings[i]->id == TAVERN)
			{
				PI->openWindow(
					curTown->getOwner(),
					curTown->buldings[i]->visibleMapObject
				);
			}
		};
		this->buttons["Slot" + std::to_string(i+1)]->addFuctionallity(fun);
	}

	this->buttons["Quit"] = std::make_shared<Button>(
		this->background.getPosition().x + 400,
		this->background.getPosition().y + 250,
		50, 30, &this->font, "OK"
		);

	this->buttons["Quit"]->addFuctionallity([=]() {this->close(); });


	this->interactiveElem.push_back(this->buttons["Quit"]);
	this->interactiveElem.push_back(this->buttons["Slot1"]);
	this->interactiveElem.push_back(this->buttons["Slot2"]);
	this->interactiveElem.push_back(this->buttons["Slot3"]);
	this->interactiveElem.push_back(this->buttons["Slot4"]);
	this->interactiveElem.push_back(this->buttons["Slot5"]);
	this->interactiveElem.push_back(this->buttons["Slot6"]);
}


TownWindow::~TownWindow()
{
}

BuildingsList::BuildingsList(std::vector<BuildingID> list, int slot)
	: WindowObject(400,300,200,500,GH.globalFont), avaibleBuildingList(list),slot(slot)
{
	this->background.setOutlineThickness(2);
	this->background.setOutlineColor(sf::Color::Yellow);
	for (int i = 0 ; i < this->avaibleBuildingList.size() ; i++)
	{
		std::string name = buildingStats[avaibleBuildingList[i]].name;
		this->addText(name, sf::Vector2f(30, 50 * i + 30));
	}
	this->buttons["Quit"] = std::make_shared<Button>(
		this->background.getPosition().x + 250,
		this->background.getPosition().y + 300,
		50, 30, &this->font, "OK"
		);

	this->buttons["Quit"]->addFuctionallity([=]() {this->close(); });
	this->interactiveElem.push_back(this->buttons["Quit"]);

	
}

void BuildingsList::addButton(std::shared_ptr<Button> btn)
{
	std::string temp = "Build" + this->buttons.size();
	this->buttons[temp] = btn;
	this->buttons[temp]->setPos(
		this->background.getPosition().x + 130,
		this->background.getPosition().y + (this->buttons.size() - 2) * 50.f + 30
	);
	this->interactiveElem.push_back(btn);
}

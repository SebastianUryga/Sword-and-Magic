#pragma once
#include "WindowObject.h"
#include "Monser.h"
class GarrnisonSlot;
class WindowObject;
class Button;
struct Troop;
// nazwa do zmiany na cos w rodzaju SelectingCreatureWin
class SelectionWindow : public WindowObject
{
private:
    std::shared_ptr<Button> decrementingBtn;
    std::shared_ptr<Button> incrementingBtn;
    class ClickablePortrait :public InterfaceElem
    {
    public:
        sf::Sprite sprite;
        std::function<void()> onClick;
        Monster id;
        void clickLeft(bool down, bool priviesState) ;
        void clickRight(bool down, bool priviesState) ;
        ClickablePortrait(Monster id);

    };
    std::vector<std::shared_ptr<ClickablePortrait>> creaturePortraits;

    int troopQuantity;
    Monster selectedCreature;
    Troop& troopToEdit;
public:

    SelectionWindow(Troop& troop);
    ~SelectionWindow();

    void render(sf::RenderTarget* target) override;
};


#pragma once
class GarrnisonSlot;
class WindowObject;
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
        ClickablePortrait(Monster id) : id(id)
        {
            this->sprite.setTexture(*graphics2.creaturesTextures[id].portrait);
            /*
            this->sprite.setTexture(*graphics.allCreaturePortraits);
            this->sprite.setTextureRect(Graphics::selectPortrait(id));
            */
        }

    };
    std::vector<std::shared_ptr<ClickablePortrait>> creaturePortraits;

    int troopQuantity;
    Monster selectedCreature;
    Troop& troopToEdit;
public:

    SelectionWindow(Troop& troop);
    ~SelectionWindow() {}


    void render(sf::RenderTarget* target) override;
};


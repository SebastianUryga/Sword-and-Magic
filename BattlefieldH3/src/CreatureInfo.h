#pragma once
#include "WindowObject.h"
#include "Monser.h"

class Monster;
class WindowObject;
class BattleUnit;

class CreatureInfo :
    public WindowObject
{
public:
    sf::Sprite portrait;
    std::vector<sf::Sprite> castedSpellIcons;

    CreatureInfo(float x, float y, Monster type);
    CreatureInfo(float x, float y, BattleUnit* unit);
    virtual ~CreatureInfo();

    Monster type;
    void render(sf::RenderTarget* target) override;
};


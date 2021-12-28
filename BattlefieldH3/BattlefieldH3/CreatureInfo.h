#pragma once


#include "Monser.h"
class Monster;
class WindowObject;

class CreatureInfo :
    public WindowObject
{
public:
    sf::Sprite portrait;

    CreatureInfo(float x, float y, Monster type);
    CreatureInfo(float x, float y, BattleUnit* unit);
    virtual ~CreatureInfo();

    Monster type;
    void render(sf::RenderTarget* target) override;
};


#pragma once
#include "Monser.h"
#include "AnimationComponent.h"
#include "PCH.hpp"

static class AnimationInitializer
{
private:
	static std::map<Monster,std::shared_ptr<AnimationComponent>> animators;
public:
	static void setUpBattleUnitAnimation();

};


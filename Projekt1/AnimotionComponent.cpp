#include "pch.h"
#include "AnimotionComponent.h"


AnimotionComponent::AnimotionComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: sprite(sprite),textureSheet(textureSheet),lastAnimation(nullptr)
{
}


AnimotionComponent::~AnimotionComponent()
{
	for (auto &i : this->animations)
	{
		delete i.second;
	}
}

void AnimotionComponent::addAnimotion(std::string key,
	float animationTimer, int start_frame_x, int start_frame_y,
	int frames_x, int frames_y, int width, int height, bool turn)
{
	this->animations[key] = new Animation(this->sprite,
		this->textureSheet, animationTimer, start_frame_x,
		start_frame_y, frames_x, frames_y, width, height, turn);
}

void AnimotionComponent::paly(const std::string key, const float & dt)
{
	if (this->lastAnimation != this->animations[key])
	{
		if (this->lastAnimation == nullptr)
			this->lastAnimation = this->animations[key];
		else
		{
			//Flip horizontally
			if (this->lastAnimation->turn != this->animations[key]->turn)
			{
				if (this->sprite.getScale().x < 0)
				{
					this->sprite.setScale(1, 1);
					this->sprite.setOrigin(32,32);
				}
				else
				{
					this->sprite.setOrigin(64,32);
					this->sprite.setScale(-1, 1);	
				}
			}
			this->lastAnimation->reset();
			this->lastAnimation = this->animations[key];
		}
	}

	this->animations[key]->play(dt);
}



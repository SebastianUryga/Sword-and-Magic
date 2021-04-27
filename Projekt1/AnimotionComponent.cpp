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
	int frames_x, int frames_y, int width, int height,
	bool turn, sf::Vector2f orgin, float tileWidth)
{
	this->animations[key] = new Animation(this->sprite,
		this->textureSheet, animationTimer, start_frame_x,
		start_frame_y, frames_x, frames_y, width, height,
		turn, orgin, tileWidth);
}

void AnimotionComponent::play(const std::string key, const float & dt, bool flipHorizontally, bool inversely )
{
	if (this->lastAnimation != this->animations[key])
	{
		if (this->lastAnimation == nullptr)
			this->lastAnimation = this->animations[key];
		else
		{
			//Flip horizontally
			this->animations[key]->reset(inversely);
				sf::IntRect tile;
				tile.left = this->animations[key]->orgin.x;
				tile.top = this->animations[key]->orgin.y;
				int width = this->animations[key]->tileWidth;
				if (flipHorizontally)
				{
					this->sprite.setOrigin((tile.left + width), tile.top);
					this->sprite.setScale(-1, 1);
				}
				else
				{
					this->sprite.setScale(1, 1);
					this->sprite.setOrigin(tile.left, tile.top);
				}
		
			this->lastAnimation->reset(inversely);
			this->lastAnimation = this->animations[key];
		}
	}
	
	this->animations[key]->play(dt,inversely);
}

bool AnimotionComponent::playedOnce(const std::string key)
{
	return this->animations[key]->playedOnce;

}

bool AnimotionComponent::playedHalf(const std::string key)
{
	auto anim = this->animations[key];
	if(anim->currnet_frame.left < (anim->last_frame* anim->width) / 2)
		return false;
	else
		return true;
}



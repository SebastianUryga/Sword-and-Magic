#include "AnimationComponent.h"

AnimationComponent::Animation::Animation(sf::Sprite & sprite, sf::Texture & textureSheet,
	float animationTimer, int start_frame_x, int start_frame_y,
	int frames_x, int frames_y, int width, int height,
	bool turn, sf::Vector2f orgin, float tileWidth) :
	sprite(sprite),
	textureSheet(textureSheet),
	animationTimer(animationTimer),
	first_frame(start_frame_x),
	last_frame(start_frame_x + frames_x),
	row(start_frame_y),
	width(width),
	height(height),
	turn(turn),
	orgin(orgin),
	tileWidth(tileWidth),
	frames_y(frames_y)
{
	this->playedOnce = false;
	this->timer = 0.f;
	this->speed = 10.f;
	this->currnet_frame = sf::IntRect(first_frame * width, row * height, width, height);
	this->sprite.setTexture(textureSheet, true);
	this->sprite.setTextureRect(currnet_frame);
}

void AnimationComponent::Animation::play(const float& dt, bool inversely)
{
	// Set Frame
	this->sprite.setTextureRect(currnet_frame);

	this->timer += speed * dt;
	if (this->timer > animationTimer)
	{
		//reset timer;
		this->timer = 0.f;
		//Animate
		if ((!inversely && this->currnet_frame.left < last_frame * width) || (inversely && this->currnet_frame.left > first_frame * width))
		{

			if (inversely)
				this->currnet_frame.left -= width;
			else
				this->currnet_frame.left += width;
		}
		else
		{
			if (inversely)
				this->currnet_frame.left = last_frame * width;
			else
				this->currnet_frame.left = first_frame * width;
			this->playedOnce = true;
		}
	}
}

void AnimationComponent::Animation::reset(bool inversely)
{
	this->playedOnce = false;
	this->timer = 0;
	if (inversely)
		this->currnet_frame.left = last_frame * width;
	else
		this->currnet_frame.left = first_frame * width;
}

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: sprite(sprite), textureSheet(textureSheet), lastAnimation(nullptr)
{
}


AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimotion(std::string key,
	float animationTimer, int start_frame_x, int start_frame_y,
	int frames_x, int frames_y, int width, int height,
	bool turn, sf::Vector2f orgin, float tileWidth)
{
	this->animations[key] = new Animation(this->sprite,
		this->textureSheet, animationTimer, start_frame_x,
		start_frame_y, frames_x, frames_y, width, height,
		turn, orgin, tileWidth);
}

void AnimationComponent::play(const std::string key, const float& dt, bool flipHorizontally, bool inversely)
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
			tile.left = (int)this->animations[key]->orgin.x;
			tile.top = (int)this->animations[key]->orgin.y;
			int width = this->animations[key]->tileWidth;
			if (flipHorizontally)
			{
				this->sprite.setOrigin((float)(tile.left + width), (float)tile.top);
				this->sprite.setScale(-1, 1);
			}
			else
			{
				this->sprite.setScale(1, 1);
				this->sprite.setOrigin((float)tile.left, (float)tile.top);
			}

			this->lastAnimation->reset(inversely);
			this->lastAnimation = this->animations[key];
		}
	}
	this->animations[key]->play(dt, inversely);
}

bool AnimationComponent::playedOnce(const std::string key)
{
	return this->animations[key]->playedOnce;

}

bool AnimationComponent::playedHalf(const std::string key)
{
	auto anim = this->animations[key];
	if (anim->currnet_frame.left < (anim->last_frame * anim->width) / 2)
		return false;
	else
		return true;
}

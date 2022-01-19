#include "Animator.h"


Animator::Animator(sf::Sprite& sprite)
	: sprite(sprite)
{
}

Animator::~Animator()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void Animator::addAnimotion(std::string key,
	std::vector<std::shared_ptr<sf::Texture>>& textures,
	float animationTimer,
	int width, int height,
	sf::Vector2f origin, float tileWidth)
{
	for (auto texture : textures)
		assert(texture != nullptr);

	this->animations[key] = new Animation(this->sprite,
		textures, animationTimer,
		width, height,
		origin, tileWidth);
}

void Animator::play(const std::string key, const float& dt, bool flipHorizontally, bool inversely)
{
	if (this->lastAnimation != this->animations[key])
	{
		if (this->lastAnimation == nullptr)
			this->lastAnimation = this->animations[key];
		else
		{
			//Flip horizontally
			this->animations[key]->reset(inversely);
			
			this->lastAnimation->reset(inversely);
			this->lastAnimation = this->animations[key];
		}
	}
	sf::IntRect tile;
	tile.left = (int)this->animations[key]->origin.x;
	tile.top = (int)this->animations[key]->origin.y;
	int width = this->animations[key]->tileWidth;
	if (flipHorizontally)
	{
		this->sprite.setOrigin((float)(tile.left + width), (float)tile.top);
		if(this->sprite.getScale().x > 0)
			this->sprite.scale(-1, 1);
	}
	else
	{
		if (this->sprite.getScale().x < 0)
			this->sprite.scale(-1, 1);
		this->sprite.setOrigin((float)tile.left, (float)tile.top);
	}
	this->animations[key]->play(dt, inversely);
}

bool Animator::playedOnce(const std::string key)
{
	return this->animations[key]->playedOnce;

}
bool Animator::playedHalf(const std::string key)
{
	auto anim = this->animations[key];
	if (anim->currentFrame < anim->textures.size() / 2)
		return false;
	else
		return true;
}
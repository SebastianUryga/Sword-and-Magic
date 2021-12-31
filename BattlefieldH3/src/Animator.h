#pragma once
#include "PCH.hpp"


class Animator
{
public:
	class Animation
	{
	public:
		Animation(sf::Sprite& sprite,
			std::vector<std::shared_ptr<sf::Texture>>& textures,
			float animationTimer,
			int width, int height,
			sf::Vector2f origin, float tileWidth) :
			sprite(sprite),
			textures(textures),
			animationTimer(animationTimer),
			width(width),
			height(height),
			origin(origin),
			tileWidth(tileWidth)
			
		{}
		std::vector<std::shared_ptr<sf::Texture>>& textures;
		sf::Sprite& sprite;
		sf::Vector2f origin;
		float tileWidth;
		float animationTimer;
		int currentFrame = 0;
		float timer= 0.f;
		int width;
		int height;
		float speed= 10.f;
		bool playedOnce = false;
		void play(const float& dt, bool inversely)
		{
			// Set Frame

			this->sprite.setTexture(*textures[currentFrame]);

			this->timer += speed * dt;
			if (this->timer > animationTimer)
			{
				if (!inversely)
				{
					if (++currentFrame >= textures.size())
					{
						currentFrame = 0;
						this->playedOnce = true;
					}
					
				}
				else
				{
					if (--currentFrame <= 0)
					{
						currentFrame = (int)textures.size()-1;
						this->playedOnce = true;
					}
				}
				//reset timer;
				this->timer = 0.f;
			}
			
		}
		void reset(bool inversely)
		{
			if (!inversely)
				currentFrame = 0;
			else
				currentFrame = (int)textures.size()-1;
			this->playedOnce = false;
			this->timer = 0;
		}
	};
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation = nullptr;

	sf::Sprite& sprite;
	Animator(sf::Sprite& sprite);
	virtual ~Animator();
	void play(const std::string key, const float& dt, bool flipHorizontally, bool inversely = false);
	bool playedOnce(const std::string key);
	bool playedHalf(const std::string key);
	void addAnimotion(std::string key, std::vector<std::shared_ptr<sf::Texture>>& textures,
		float animationTimer, int width, int height,
		sf::Vector2f origin, float tileWidth);
};


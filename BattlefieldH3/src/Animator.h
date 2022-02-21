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
			sf::Vector2f origin, float tileWidth);
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

		void play(const float& dt, bool inversely);
		
		void reset(bool inversely);
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


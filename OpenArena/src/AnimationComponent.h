#pragma once
#include "PCH.hpp"
class AnimationComponent
{
private:
	class Animation
	{
	public:
		Animation(sf::Sprite& sprite, sf::Texture& textureSheet,
			float animationTimer, int start_frame_x, int start_frame_y,
			int frames_x, int frames_y, int width, int height,
			bool turn, sf::Vector2f orgin, float tileWidth);
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		int first_frame;
		int last_frame;
		int row;
		int width;
		int height;
		bool turn;
		sf::Vector2f orgin;
		float tileWidth;
		int frames_y;
		bool playedOnce;
		float timer;
		float speed;
		sf::IntRect currnet_frame;
		//Functions
		void play(const float& dt, bool inversely);

		void reset(bool inversely);
		
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	void addAnimotion(std::string key,
		float animationTimer, int start_frame_x, int start_frame_y,
		int frames_x, int frames_y, int width, int height,
		bool ch, sf::Vector2f orgin, float tileWidth);

	void play(const std::string key, const float& dt, bool flipHorizontally, bool inversely = false);
	bool playedOnce(const std::string key);
	bool playedHalf(const std::string key);
};

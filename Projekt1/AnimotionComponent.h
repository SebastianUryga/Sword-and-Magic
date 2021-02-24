#pragma once
class AnimotionComponent
{
private:
	class Animation
	{
	public:
		Animation(sf::Sprite& sprite,sf::Texture& textureSheet,
			float animationTimer, int start_frame_x, int start_frame_y,
			int frames_x, int frames_y, int width, int height, bool turn)
			:sprite(sprite),textureSheet(textureSheet),animationTimer(animationTimer),
			first_frame(start_frame_x), last_frame(start_frame_x + frames_x),
			row(start_frame_y), width(width),height(height),turn(turn)
		{
			this->timer = 0.f;
			this->speed = 10.f;
			this->currnet_frame = sf::IntRect(first_frame*width, row*height, width, height);
			this->sprite.setTexture(textureSheet,true);
			this->sprite.setTextureRect(currnet_frame);
		}
		//Variables
		sf::Texture& textureSheet;
		sf::Sprite& sprite;
		bool turn;
		int width;
		int height;
		float timer;
		float animationTimer;
		float speed;
		int row;
		int first_frame;
		sf::IntRect currnet_frame;
		int last_frame;
		//Functions
		void play(const float& dt)
		{
			// Set Frame
			this->sprite.setTextureRect(currnet_frame);
			
			this->timer += speed * dt;
			if (this->timer > animationTimer)
			{
				//reset timer;
				this->timer = 0.f;
				//Animate
				if (this->currnet_frame.left < last_frame * width)
				{
					this->currnet_frame.left += width;
				}
				else
				{
					this->currnet_frame.left = first_frame * width;
				}
			}
		}

		void reset()
		{
			this->timer = animationTimer;	
			this->currnet_frame.left = first_frame * width;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
public:
	AnimotionComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimotionComponent();

	void addAnimotion(std::string key,
		float animationTimer, int start_frame_x, int start_frame_y,
		int frames_x, int frames_y, int width, int height, bool ch);

	void paly(const std::string key, const float& dt);

};


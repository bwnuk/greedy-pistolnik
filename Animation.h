#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;

public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void Update(int row, float deltaTime, bool Stay);

	sf::IntRect uvRect;
};


#pragma once
//Animacja postaci, ruch(WASD)
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture & texture, sf::Vector2u imageCount, float switchtime);
	~Animation();
	void Update(unsigned int row, float deltaTime, bool Stay, float turboSpeed);
	sf::IntRect uvRect;
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totaltime;
	float switchtime;
};


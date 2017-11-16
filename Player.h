#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window, sf::View view);
	//sf::View view;
	Collider GetCollider() { return Collider(body); }
	
	sf::Vector2f GetPosition() { return  body.getPosition(); }

private:
	Animation animation;
	sf::RectangleShape body;
	bool Stay;
	unsigned int row;
	float speed;

};


#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
private:
	sf::RectangleShape& body;

public:
	Collider(sf::RectangleShape& body);
	~Collider();

	bool CheckCollision(Collider& other, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
	void Move(float dx, float dy) { body.move(dx, dy); }

};


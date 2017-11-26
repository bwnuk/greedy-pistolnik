#pragma once
//Ustawienie pozycji poczatkowej gracza, animacja gracza
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Account.h"

class player
	:public Account
{
public:
	player(sf::Texture &texture, sf::Vector2u imageCount, float scale_body, float switchTime, float speed);
	~player();
	sf::Text AccountText;
	sf::Text AccountTextMoney;
	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window, sf::View view);
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetPosition() const { return  body.getPosition(); }
	float collisionSize;
	enum Direction { left, right, up, down };
	Direction direction;
private:
	sf::Font font;
	Animation animation;
	sf::RectangleShape body;
	bool Stay;
	unsigned int row;
	float speed;
	sf::Vector2f sizeBody;
};


#include "stdafx.h"
#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
	:animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	Stay = true;
	body.setSize(sf::Vector2f(120.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(400, 200);
	body.setTexture(texture);
	//view.setCenter(400.0f, 200.0f);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed*deltaTime;

	//view.move(movement);

	if (movement.x > 0.0f)
		row = 2;
	if (movement.x < 0.0f)
		row = 1;
	if (movement.y < 0.0f)
		row = 3;
	if (movement.y > 0.0f)
		row = 0;
	Stay = false;


	if (movement.y == 0 && movement.x == 0)
		Stay = true;
	animation.Update(row, deltaTime, Stay);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}


void Player::Draw(sf::RenderWindow & window, sf::View view)
{
	window.draw(body);
	window.setView(view);
}

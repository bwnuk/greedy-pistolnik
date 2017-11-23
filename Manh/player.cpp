#include "player.h"

player::player(sf::Texture &texture, sf::Vector2u imageCount, float scale_body, float switchTime, float speed)
	:animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	Stay = true;
	sizeBody = sf::Vector2f(texture.getSize());
	sizeBody.y = sizeBody.y / imageCount.y * scale_body;
	sizeBody.x = sizeBody.x / imageCount.x * scale_body;
	body.setSize(sizeBody);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(432, 332);
	body.setTexture(&texture);
	collisionSize = sizeBody.y + 10.0f;
}

player::~player()
{
}

void player::Update(float deltaTime)
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
	if (movement.x > 0.0f)
		row = 3;
	if (movement.x < 0.0f)
		row = 1;
	if (movement.y < 0.0f)
		row = 0;
	if (movement.y > 0.0f)
		row = 2;
	Stay = false;
	if (movement.y == 0 && movement.x == 0)
		Stay = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		movement.x *= 2.0f;
		movement.y *= 2.0f;
		animation.Update(row, deltaTime, Stay, 3.0f);
	}
	else
		animation.Update(row, deltaTime, Stay, 1.0f);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void player::Draw(sf::RenderWindow &window, sf::View view)
{
	window.draw(body);
	window.setView(view);
}

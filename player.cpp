#include "player.h"

player::player(sf::Texture &texture, sf::Vector2u imageCount, float scale_body, float switchTime, float speed)
	:animation(texture, imageCount, switchTime)
{
	if (!font.loadFromFile("images/jendrzej.ttf"))
		exit(10);
	this->speed = speed;
	row = 0;
	Stay = true;
	sizeBody = sf::Vector2f(texture.getSize());
	sizeBody.y = sizeBody.y / imageCount.y * scale_body;
	sizeBody.x = sizeBody.x / imageCount.x * scale_body;
	body.setSize(sizeBody);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(500.0f, 500.0f);
	body.setTexture(&texture);
	collisionSize = sizeBody.y + 10.0f;

	//Text
	set_money(500);
	AccountText.setCharacterSize(30);
	AccountText.setFont(font);
	AccountText.setString("Money: ");
	AccountTextMoney.setCharacterSize(30);
	AccountTextMoney.setFont(font);
	
	AccountText.setPosition(800, 0.0f);
	AccountTextMoney.setPosition(900.0f, 0.0f);

	//direction = down;
}

player::~player()
{
}

void player::Update(float deltaTime)
{
	AccountTextMoney.setString(std::to_string(get_money()));
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		movement.y -= speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		movement.y += speed*deltaTime;
	if (movement.x > 0.0f)
	{
		row = 2;
		direction = right;
	}
	if (movement.x < 0.0f)
	{
		row = 1;
		direction = left;
	}

	if (movement.y < 0.0f)
	{
		row = 3;
		direction = up;
	}
	if (movement.y > 0.0f)
	{
		row = 0;
		direction = down;
	}

	Stay = false;
	if (movement.y == 0 && movement.x == 0)
		Stay = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		movement.x *= 2.0f;
		movement.y *= 2.0f;
		animation.Update(row, deltaTime, Stay, 2.0f);
	}
	else
		animation.Update(row, deltaTime, Stay, 1.0f);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	/*AccountText.move(movement);
	AccountTextMoney.move(movement);*/
}

void player::Draw(sf::RenderWindow &window, sf::View view)
{
	window.draw(body);
	//window.draw(AccountText);
	//window.draw(AccountTextMoney);
	window.setView(view);
}

#include "enemy.h"
#include "Animation.h"
#include <iostream> //wypierdolic


enemy::enemy(sf::Texture &enemy_texture)
{
	this->enemy_texture = enemy_texture;
	
	//body.setPosition(sf::Vector2f(rand() % 1280, rand() % 720)); // tutaj zrobic nie stale wartosci tylko zalezne od okna
		sizeBody = sf::Vector2f(enemy_texture.getSize());
		sizeBody.x = sizeBody.x / 7.0f;
		body.setSize(sizeBody);
		body.setTexture(&enemy_texture);
		body.setTextureRect(sf::IntRect(0, 0, ceil(sizeBody.x), ceil(sizeBody.y)));
}

void enemy::set_name(std::string n)
{
	name = n;
}

std::string enemy::get_name()
{
	return name;
}

void enemy::set_hp(int h)
{
	hp = h;
}

int enemy::get_hp()
{
	return hp;
}

void enemy::set_lvl(int l)
{
	lvl = l;
}

int enemy::get_lvl()
{
	return lvl;
}

void enemy::set_speed(double s)
{
	speed = s;
}

double enemy::get_speed()
{
	return speed;
}

void enemy::Draw(sf::RenderWindow &window)
{
	window.draw(body);
}

enemy::~enemy()
{
}

void enemy::Position(sf::Vector2f pos)
{
	body.setPosition(pos);
}


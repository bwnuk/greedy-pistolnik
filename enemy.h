#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>

class enemy
{
public:
	enemy(sf::Texture &);
	void set_name(std::string);
	std::string get_name();
	void set_hp(int);
	int get_hp();
	void set_lvl(int);
	int get_lvl();
	void set_speed(double);
	double get_speed();

	void Draw(sf::RenderWindow &window);
	~enemy();
	void Position(sf::Vector2f pos);


	sf::RectangleShape body;

private:
	std::string name;
	int hp;
	int lvl;
	double speed;
	
	sf::Vector2f sizeBody;
	sf::Vector2f tempsize;
	sf::Texture enemy_texture;

};


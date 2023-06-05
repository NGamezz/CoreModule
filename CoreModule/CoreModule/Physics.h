#pragma once

#include <SFML/Graphics.hpp>

class Physics
{
private:

public:
	void circleCollision(sf::CircleShape first, sf::CircleShape second);
	void distance(sf::Vector2f a, sf::Vector2f b);
};


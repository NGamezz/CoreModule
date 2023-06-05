#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
private:
	float moveSpeedY;
	int width, height;
	bool hit = false;
	float velocity = 0.0f;
	sf::Vector2f previousPos;

public:
	sf::CircleShape testShape;
	float Radius;
	float Mass;
	float Force = 0;
	float MoveSpeedX;
	Entity(float rad, float speed, int positionX, int positionY, sf::Color, int h, int w, float mass);
	void DrawEntity(sf::RenderWindow* window, bool player);
	void ChangeDirection();
	void SpeedCalculation(bool player, float force, float mass, sf::Vector2f previousPos, sf::Vector2f currentPos);
};


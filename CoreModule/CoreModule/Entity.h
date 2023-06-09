#pragma once

#include "Vector2.h"
#include <iostream>
#include "Physics.h"

class Entity
{
private:
	float moveSpeedY;
	int width, height;
	bool hit = false;
	float velocity = 0.0f;

public:
	bool right = false, left = false, zero = false;

	sf::Clock clock;
	sf::CircleShape testShape;
	float Radius;
	CustomPhysics::Vector2f position;
	float Mass;
	float Force = 0;
	float MoveSpeedX;
	Entity(float rad, float speed, int positionX, int positionY, sf::Color, int h, int w, float mass);
	void DrawEntity(sf::RenderWindow* window);
	void ChangeDirection();
	void SpeedCalculation(float force, float mass);
};


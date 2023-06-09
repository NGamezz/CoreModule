#pragma once

#include "Entity.h"
#include "Vector2.h"
#include "SFML/Graphics.hpp"

class Player
{
private:
	float moveSpeedY;
	int width, height;
	bool hit = false;
	float velocity = 0.0f;
	bool leftKey, rightKey;
	float time;
	float deceleration = 0.05f;

public:
	bool right = false, left = false, zero = false;

	CustomPhysics::Vector2f position;
	sf::Clock clock;
	sf::CircleShape testShape;
	float Radius;
	float Mass;
	float Force = 0;
	float MoveSpeedX;
	void DrawEntity(sf::RenderWindow* window);
	void SpeedCalculation();
	void playerMovement();
	Player(float rad, float speed, int positionX, int positionY, sf::Color, int h, int w, float mass);
};


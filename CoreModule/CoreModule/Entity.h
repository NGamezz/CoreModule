#pragma once

#include "Vector2.h"
#include "Physics.h"

class Entity
{
private:
	float moveSpeedY;
	int width, height;
	bool hit = false;
	float velocityY = 0.0f;
	float velocityX = 0.0f;
	sf::Clock dartelClock;

public:
	bool right = false, left = false, zero = false;
	sf::Sprite parachuteSprite;
	sf::Clock clock;
	float Radius;
	CustomPhysics::Vector2f position;
	float Mass;
	float ForceY = 0;
	float ForceX = 0;
	float MoveSpeedX;
	Entity(float rad, float speed, int positionX, int positionY, int h, int w, float mass, sf::Texture& spriteTexture);
	void DrawEntity(sf::RenderWindow* window);
	void ChangeDirection();
	void SpeedCalculation(float forceY, float forceX);
};


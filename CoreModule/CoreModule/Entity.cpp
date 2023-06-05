#include "Entity.h"
#include <iostream>
#include "Physics.h"

Entity::Entity(float rad, float speed, int positionX, int positionY, sf::Color color, int h, int w, float m)
{
	Radius = rad;
	testShape = sf::CircleShape(Radius);
	testShape.setFillColor(color);
	testShape.setPosition(positionX, positionY);

	Mass = m;

	width = w;;
	height = h;

	testShape.setOrigin((Radius / 2), (Radius / 2));

	MoveSpeedX = speed;
	moveSpeedY = speed;
}

void Entity::ChangeDirection()
{
	velocity = 0.0f;
	testShape.setPosition(std::rand() % width, 0);
}

void Entity::SpeedCalculation(bool player, float force, float mass, sf::Vector2f previousPos, sf::Vector2f currentPos)
{
	std::clock_t timer;
	timer = clock();
	float acceleration = player ? force / mass : 9.81;
	velocity = velocity + (acceleration * timer);

	if (velocity >= 5)
	{
		velocity = 5;
	}
	if (velocity < -5)
	{
		velocity = -5;
	}

	player ? MoveSpeedX = velocity : moveSpeedY = velocity;
	std::cout << velocity << std::endl;
}

void Entity::DrawEntity(sf::RenderWindow* window, bool player)
{
	if (player)
	{
		SpeedCalculation(true, Force, Mass, previousPos, testShape.getPosition());
		testShape.move(MoveSpeedX, 0);
	}
	else
	{
		SpeedCalculation(false, Force, Mass, previousPos, testShape.getPosition());
		testShape.move(MoveSpeedX, moveSpeedY);
	}

	if (!player)
	{
		sf::Vector2f testShapePosition = testShape.getPosition();
		if (testShapePosition.x >= width || testShapePosition.x <= 0)
		{
			MoveSpeedX *= -1;
		}
		if (testShapePosition.y > height || testShapePosition.y < 0)
		{
			testShape.setPosition(std::rand() & width, 0);
		}
	}

	window->draw(testShape);
}

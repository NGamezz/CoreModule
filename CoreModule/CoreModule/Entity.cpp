#include "Entity.h"

Entity::Entity(float rad, float speed, int positionX, int positionY, sf::Color color, int h, int w, float m)
{
	Radius = rad;
	testShape = sf::CircleShape(Radius);
	testShape.setFillColor(color);
	testShape.setPosition(positionX, positionY);

	Mass = m;

	Force = 5.0f;

	position = CustomPhysics::Vector2f(positionX, positionY);

	width = w;;
	height = h;

	testShape.setOrigin((Radius / 2), (Radius / 2));

	MoveSpeedX = speed;
	moveSpeedY = speed;
}

void Entity::ChangeDirection()
{
	velocity = 0.0f;
	Force = 5.0f;
	clock.restart().asSeconds();

	CustomPhysics::Vector2f randomPos = CustomPhysics::Vector2f(std::rand() % width, std::rand() % -100);
	position = randomPos;

	testShape.setPosition(position.X, position.Y);
}

void Entity::SpeedCalculation(float force, float mass)
{
	float time = clock.getElapsedTime().asSeconds();

	if (Force != 0)
	{
		float acceleration = force / mass;
		velocity = velocity + (acceleration * time);

		CustomPhysics::Physics<float>::Clamp(velocity, -7, 7);

		moveSpeedY = velocity;
	}
}

void Entity::DrawEntity(sf::RenderWindow* window)
{
	SpeedCalculation(Force, Mass);

	position += CustomPhysics::Vector2f(MoveSpeedX, moveSpeedY);

	testShape.setPosition(position.X, position.Y);

	if (position.X >= width || position.X <= 0)
	{
		MoveSpeedX *= -1;
	}
	if (position.Y > height || position.Y < 0)
	{
		ChangeDirection();
	}

	window->draw(testShape);
}

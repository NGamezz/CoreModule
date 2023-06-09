#include "Player.h"

Player::Player(float rad, float speed, int positionX, int positionY, sf::Color color, int h, int w, float m)
{
	Radius = rad;
	testShape = sf::CircleShape(Radius);
	testShape.setFillColor(color);
	testShape.setPosition(positionX, positionY);

	Mass = m;

	position = CustomPhysics::Vector2f(positionX, positionY);

	Force = 5.0f;

	width = w;;
	height = h;

	testShape.setOrigin((Radius / 2.0f), (Radius / 2.0f));

	MoveSpeedX = speed;
	moveSpeedY = speed;
}

void Player::playerMovement()
{
	leftKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	rightKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (leftKey && !rightKey && position.X > (width * 0.05f))
	{
		Force = -5.0f;
		if (!left)
		{
			left = true;
			zero = false;
			right = false;
			clock.restart().asSeconds();
		}
	}
	if (rightKey && !leftKey && position.X < (width * 0.95f))
	{
		Force = 5.0f;
		if (!right)
		{
			right = true;
			left = false;
			zero = false;
			clock.restart().asSeconds();
		}
	}
	if (!rightKey && !leftKey)
	{
		Force = 0.0f;
		if (!zero)
		{
			zero = true;
			left = false;
			right = false;
			clock.restart().asSeconds();
		}
	}
}

void Player::SpeedCalculation()
{
	if (position.X < width * 0.05f || position.X > width * 0.95f)
	{
		MoveSpeedX = 0.0f;
		velocity = 0.0f;

		position.X = (position.X <= (width * 0.05f)) ? (width * 0.05f) + 2.0f : (width * 0.95f) - 2.0f;
		testShape.setPosition(position.X, position.X);

		return;
	}

	time = clock.getElapsedTime().asSeconds();

	if (Force != 0.0f)
	{
		float acceleration = Force / Mass;
		velocity = velocity + (acceleration * time);

		CustomPhysics::Physics<float>::Clamp(velocity, -7.0f, 7.0f);

		MoveSpeedX = velocity;
	}

	if (Force == 0.0f)
	{
		bool left = velocity < 0;

		if (left)
		{
			velocity = CustomPhysics::Physics<float>::Min(0, velocity + deceleration);
		}
		else if (!left && velocity != 0)
		{
			velocity = CustomPhysics::Physics<float>::Max(0, velocity - deceleration);
		}

		CustomPhysics::Physics<float>::Clamp(velocity, -7.0f, 7.0f);

		MoveSpeedX = velocity;
	}
}

void Player::DrawEntity(sf::RenderWindow* window)
{
	SpeedCalculation();

	position += CustomPhysics::Vector2f(MoveSpeedX, 0.0f);

	testShape.setPosition(position.X, position.Y);
	window->draw(testShape);
}
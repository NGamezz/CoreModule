#include "Entity.h"

Entity::Entity(float rad, float speed, int positionX, int positionY, int h, int w, float m, sf::Texture& spriteTexture)
{
	Radius = rad;

	Mass = m;

	parachuteSprite.setTexture(spriteTexture);
	parachuteSprite.setScale(0.5, 0.5);
	parachuteSprite.setOrigin(parachuteSprite.getLocalBounds().width / 2, parachuteSprite.getLocalBounds().height / 2);
	parachuteSprite.setPosition(positionX, positionY);

	ForceY = 5.0f;
	ForceX = rand() % (0 - 10);

	position = CustomPhysics::Vector2f(positionX, positionY);

	width = w;;
	height = h;

	MoveSpeedX = speed;
	moveSpeedY = speed;
}

void Entity::ChangeDirection()
{
	velocityY = 0.0f;
	ForceY = 2.0f;
	clock.restart().asSeconds();

	ForceX = rand() % 5;

	CustomPhysics::Vector2f randomPos = CustomPhysics::Vector2f(std::rand() % width, std::rand() % -100);
	position = randomPos;

	parachuteSprite.setPosition(position.X, position.Y);
}

void Entity::SpeedCalculation(float forceY, float forceX)
{
	float time = clock.getElapsedTime().asSeconds();
	float dartelTime = dartelClock.getElapsedTime().asSeconds();

	if (dartelTime >= 2)
	{
		dartelClock.restart();
		ForceX *= -1;
	}

	if (ForceY != 0)
	{
		float accelerationY = forceY / Mass;
		velocityY = velocityY + (accelerationY * time);

		CustomPhysics::Physics<float>::Clamp(velocityY, -4.0f, 4.0f);

		moveSpeedY = velocityY;
	}

	if (ForceX != 0)
	{
		float accelerationX = forceX / Mass;
		velocityX = velocityX + (accelerationX * time);

		CustomPhysics::Physics<float>::Clamp(velocityX, -3.0f, 3.0f);

		MoveSpeedX = velocityX;
	}
}

void Entity::DrawEntity(sf::RenderWindow* window)
{
	SpeedCalculation(ForceY, ForceX);

	position += CustomPhysics::Vector2f(MoveSpeedX, moveSpeedY);

	parachuteSprite.setPosition(position.X, position.Y);

	//Soft Boundary
	if (position.X >= width * 0.85f && ForceX > 0 || position.X <= width * 0.15f && ForceX < 0)
	{
		ForceX *= -1;
	}

	//Hard Boundary
	if (position.X < width * 0.01f || position.X > width * 0.99f)
	{
		position.X = (position.X <= (width * 0.01f)) ? (width * 0.01f) + 0.01f : (width * 0.99f) - 0.01f;
		parachuteSprite.setPosition(position.X, position.Y);
	}

	window->draw(parachuteSprite);
}

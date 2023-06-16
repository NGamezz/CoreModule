#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Player.h"
#include "Physics.h"

void SetUpText(int characterSize, sf::Text& text, sf::Color color, int width, int height, bool score)
{
	text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
	score ? text.setPosition(width * 0.05f, height * 0.095f) : text.setPosition(width / 2.0f, height / 2.0f);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(40.0f);
}

int main()
{
	int width = 1920;
	int height = 1080;

	int scoreNumber = 0;
	bool GameOver = false;
	bool GameWon = false;

	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string path = std::string(buffer).substr(0, pos);

	std::string fontPath = path + "\\metalmania.ttf";

	sf::Texture parachuteSprite;
	if (!parachuteSprite.loadFromFile(path + "\\Illustration.png"));

	sf::Texture pacmanTexture;
	if (!pacmanTexture.loadFromFile(path + "\\pacman.png"));

	sf::Texture backGroundTexture;
	sf::Sprite backGroundSprite;
	if (!backGroundTexture.loadFromFile(path + "\\background.png"));
	backGroundSprite.setTexture(backGroundTexture);
	backGroundSprite.setScale(width / backGroundSprite.getLocalBounds().width, height / backGroundSprite.getLocalBounds().height);

	sf::Font font;
	if (!font.loadFromFile(fontPath));

	sf::Text scoreText(std::to_string(scoreNumber), font);
	SetUpText(40.0f, scoreText, sf::Color::White, width, height, true);

	sf::Text win("You Win!", font);
	SetUpText(40.0f, win, sf::Color::White, width, height, false);

	sf::Text gameOver("You Lose..", font);
	SetUpText(40.0f, gameOver, sf::Color::White, width, height, false);


	std::vector<Entity> enemies;

	sf::RenderWindow window(sf::VideoMode(width, height), "Testing Game Window");

	window.setFramerateLimit(60);

	for (int i = 0; i < 2; i++)
	{
		float randomMass = std::rand() % 80;

		enemies.push_back(Entity(80.0f, 0.075f, std::rand() % width, std::rand() % -100, height, width, randomMass, parachuteSprite));
	}

	Player player = Player(50.0f, 0.2f, (width / 2.0f), (height * 0.75f), sf::Color::Yellow, height, width, 20.0f, pacmanTexture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.draw(backGroundSprite);

		player.playerMovement();

		for (int i = 0; i < enemies.size(); i++)
		{
			if (GameWon || GameOver)
			{
				break;
			}

			if (CustomPhysics::Physics<float>::circleCollision(player.Radius, player.position, enemies[i].Radius, enemies[i].position))
			{
				scoreNumber++;
				enemies[i].ChangeDirection();
			}
			if (enemies[i].position.Y > height || enemies[i].position.Y < 0)
			{
				scoreNumber--;
				enemies[i].ChangeDirection();
			}
			enemies[i].DrawEntity(&window);
		}

		player.DrawEntity(&window);
		scoreText.setString(std::to_string(scoreNumber));

		if (scoreNumber >= 25.0f)
		{
			GameWon = true;
			GameOver = false;
		}
		if (scoreNumber <= -25.0f)
		{
			GameOver = true;
			GameWon = false;
		}

		window.draw(scoreText);
		if (GameWon)
		{
			window.draw(win);
		}
		if (GameOver)
		{
			window.draw(gameOver);
		}
		window.display();
	}
}
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

	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string path = std::string(buffer).substr(0, pos);

	std::string fontPath = path + "\\metalmania.ttf";

	sf::Font font;
	if (!font.loadFromFile(fontPath));

	int scoreNumber = 0;
	bool GameOver = false;
	bool GameWon = false;

	sf::Text score(std::to_string(scoreNumber), font);
	SetUpText(40.0f, score, sf::Color::White, width, height, true);

	sf::Text win("You Win!", font);
	SetUpText(40.0f, win, sf::Color::White, width, height, false);

	sf::Text gameOver("You Lose..", font);
	SetUpText(40.0f, gameOver, sf::Color::White, width, height, false);

	std::vector<Entity> enemies;

	std::vector<sf::Color> colours = { sf::Color::White, sf::Color::Yellow, sf::Color::Blue, sf::Color::Green };

	sf::RenderWindow window(sf::VideoMode(width, height), "Testing Game Window");

	window.setFramerateLimit(60);

	for (int i = 0; i < 1; i++)
	{
		sf::Color color = colours[std::rand() % colours.size()];

		float randomMass = std::rand() % 80;

		enemies.push_back(Entity(30.0f, 0.075f, std::rand() % width, std::rand() % -100, color, height, width, randomMass));
	}

	Player player = Player(50.0f, 0.2f, (width / 2.0f), (height * 0.75f), sf::Color::Yellow, height, width, 20.0f);

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
		window.clear(sf::Color::Black);

		player.playerMovement();

		for (int i = 0; i < enemies.size(); i++)
		{
			if (CustomPhysics::Physics<sf::CircleShape>::circleCollision(player.testShape, player.position, enemies[i].testShape, enemies[i].position))
			{
				scoreNumber++;
				enemies[i].ChangeDirection();
			}
			if (enemies[i].position.Y >= height - 5.0f)
			{
				scoreNumber--;
			}
			enemies[i].DrawEntity(&window);
		}

		player.DrawEntity(&window);
		score.setString(std::to_string(scoreNumber));

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

		window.draw(score);
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
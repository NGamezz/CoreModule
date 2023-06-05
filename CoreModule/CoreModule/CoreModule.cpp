#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

double distance(sf::Vector2f first, sf::Vector2f second)
{
	double dy = (first.y - second.y);
	double dx = (first.x - second.x);
	double distance = sqrt(pow(dy, 2) + pow(dx, 2));
	return distance;
}

bool circleCollision(sf::CircleShape first, sf::CircleShape second)
{
	double dis = distance(first.getPosition(), second.getPosition());
	return dis <= (first.getRadius() + second.getRadius()) ? true : false;
}

void playerMovement(bool leftKey, bool rightKey, Entity* player, int width)
{
	sf::Vector2f pacman1Pos = player->testShape.getPosition();

	if (leftKey && !rightKey && pacman1Pos.x > (width * 0.1))
	{
		player->Force = -5;
	}
	if (rightKey && !leftKey && pacman1Pos.x < (width * 0.9))
	{
		player->Force = 5;
	}
	if (!rightKey && !leftKey)
	{
		player->Force = 0;
	}
}

int main()
{
	/*char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string path = std::string(buffer).substr(0, pos);

	std::string fontPath = path + "\\metalmania.ttf";

	std::cout << fontPath.c_str() << std::endl;

	std::ifstream file(fontPath);
	std::cout << "Exists: " << file.good() << std::endl;

	std::string filename = "metalmania.ttf";

	sf::FileInputStream f;
	f.open(filename);*/

	/*sf::Font font;
	if (!font.loadFromFile(fontPath));*/

	/*sf::Font font;
	if (!font.loadFromStream(f))
	{
	}*/

	/*sf::Texture backGroundTexture;
	if (!backGroundTexture.loadFromFile("3997687.png"))
	{
	}*/

	sf::Clock clock;

	int scoreNumber = 0;
	sf::Text score;

	//score.setFont(font);
	score.setFillColor(sf::Color::White);
	score.setCharacterSize(15);

	std::vector<Entity> enemies;

	std::vector<sf::Color> colours = { sf::Color::White, sf::Color::Yellow, sf::Color::Blue, sf::Color::Green };

	int width = 800;
	int height = 600;
	sf::RenderWindow window(sf::VideoMode(width, height), "Testing Game Window");

	window.setFramerateLimit(60);

	for (int i = 0; i < 3; i++)
	{
		sf::Color color = colours[std::rand() % colours.size()];

		enemies.push_back(Entity(30.0f, 0.075f, std::rand() % width, std::rand() % -100, color, height, width, 20.0f));
	}

	Entity player = Entity(50.0f, 0.2f, 400.0f, 300.0f, sf::Color::Yellow, height, width, 50.0f);

	bool leftKey, rightKey;

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

		/*double previousTime = clock.getElapsedTime().asMilliseconds();
		float fps = 1 / (clock.getElapsedTime().asMilliseconds() - previousTime);
		std::cout << fps << std::endl;*/

		leftKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		rightKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		playerMovement(leftKey, rightKey, &player, width);

		for (int i = 0; i < enemies.size(); i++)
		{
			if (circleCollision(player.testShape, enemies[i].testShape))
			{
				scoreNumber++;
				enemies[i].ChangeDirection();
			}

			enemies[i].DrawEntity(&window, false);
		}
		player.DrawEntity(&window, true);

		score.setString(std::to_string(scoreNumber) + "Testing");
		window.draw(score);
		window.display();
	}
}


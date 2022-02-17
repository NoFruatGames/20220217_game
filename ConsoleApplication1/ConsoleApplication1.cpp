#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

int main()
{
	float x_begin = 80;
	float y_begin = 80;
	float x_d = x_begin;
	float y_d = y_begin;
	RenderWindow window(VideoMode(800, 600), "SFML Application");
	Texture texture;
	Texture texture_enemy;
	texture.loadFromFile("c.png");
	texture_enemy.loadFromFile("8.png");
	Sprite sprite(texture);
	Sprite enemy(texture_enemy);

	sprite.setScale(5, 5);
	enemy.setScale(0.3, 0.3);
	enemy.setPosition(400, 300);

	RectangleShape ramke(Vector2f(700, 500));
	ramke.setOutlineThickness(10);
	ramke.setOutlineColor(Color::Black);
	ramke.setFillColor(Color(0, 255, 255));
	ramke.setPosition(50, 50);


	float time=0, delay=0.1;

	Clock clock;
	Clock gametime;

	Font font;
	font.loadFromFile("calibri.ttf");
	Text text("0:00", font);
	text.setPosition(Vector2f(50, 0));
	text.setFillColor(Color::Black);
	bool dead = false;
	int gameSeconds=0;
	int gameMinutes = 0;
	while (window.isOpen())
	{
		Event event;
		float t = clock.getElapsedTime().asSeconds();
		clock.restart();
		time += t;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					if(y_d - 20 >= 23)
						y_d -= 20;
				}
				if (event.key.code == Keyboard::Down)
				{
					if(y_d + 20 <= 460)
						y_d += 20;
				}
				if (event.key.code == Keyboard::Left)
				{
					if(x_d - 20 >= 40)
						x_d -= 20;
				}
				if (event.key.code == Keyboard::Right)
				{
					if(x_d + 20 <= 670)
						x_d += 20;
				}
			}
		}
		if (time > delay)
		{
			float x = enemy.getPosition().x;
			float y = enemy.getPosition().y;
			if (x > x_d + 40)
				x -= 5;
			else
				x += 5;

			if (y > y_d + 40)
				y -= 5;
			else
				y += 5;
			std::cout << "X: " << x << " x_d: " << x_d << " y: " << y << " y_d: " << y_d << '\n';
			if ((x_d + 40 >= x && x_d + 40 <= x+150) && (y_d + 40 >= y && y_d + 40 <= y+120))
				dead = true;
			enemy.setPosition(x, y);
			time = 0;

		}

		gameSeconds = gametime.getElapsedTime().asSeconds();
		while (gameSeconds > 60)
		{
			gameSeconds -= 60;
			gameMinutes += 1;
			gametime.restart();
		}
		text.setString(std::to_string(gameMinutes)+":"+std::to_string(gameSeconds));
		if (dead)
		{
			x_d = x_begin;
			y_d = y_begin;
			enemy.setPosition(400, 300);
			dead = false;
			gametime.restart();
			gameMinutes = 0;
			gameSeconds = 0;
		}


		sprite.setPosition(Vector2f(x_d, y_d));
		window.clear(Color(0, 255, 255));
		window.draw(ramke);
		window.draw(sprite);
		window.draw(enemy);
		window.draw(text);
		window.display();
	}

}
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <chrono>

using namespace sf;
class villager
{
	Texture _villagerTexture;
	Sprite _villagerSprite;
	bool _isAlive, _isVisible;
	sf::Clock _clockToShoot;
	int _random;
	float _timeVisible, _timeInvisible;

	Vector2f _RandomPos()
	{
		_random = rand() % 6;
		Vector2f ret;

		switch (_random)
		{
		case 0:
			ret = Vector2f(80, 80);
			break;
		case 1:
			ret = Vector2f(240, 80);
			break;
		case 2:
			ret = Vector2f(400, 80);
			break;
		case 3:
			ret = Vector2f(80, 320);
			break;
		case 4:
			ret = Vector2f(240, 320);
			break;
		case 5:
			ret = Vector2f(400, 320);
			break;
		}

		return(ret);
	}

public:

	villager()
	{
		_villagerTexture.loadFromFile("villager.png");
		_villagerSprite.setTexture(_villagerTexture);
		_villagerSprite.setScale(5, 5);
		_isAlive = true;
		_isVisible = false;
		_timeVisible = 0.5;
		_timeInvisible = 6;
	}

	bool IsAlive()
	{
		return (_isAlive);
	}

	bool IsActive()
	{
		return (_isAlive && _isVisible);
	}

	bool WasShooted(Vector2f crosshairPosition)
	{
		FloatRect bounds = _villagerSprite.getGlobalBounds();
		return (bounds.contains(crosshairPosition.x, crosshairPosition.y));
	}

	void Destroy()
	{
		_isAlive = false;
	}

	void Draw(RenderWindow* wnd)
	{
		wnd->draw(_villagerSprite);
	}

	void Update(RenderWindow* wnd)
	{
		if (!_isAlive)
		{
			return;
		}

		if (!_isVisible)
		{
			if (_clockToShoot.getElapsedTime().asSeconds() > _timeInvisible)
			{
				_clockToShoot.restart();
				if (rand() % 100 > 1)
				{
					_isVisible = true;
					_villagerSprite.setPosition(_RandomPos());
				}
			}
		}
		else
		{
			if (_clockToShoot.getElapsedTime().asSeconds() > _timeVisible)
			{
				_isVisible = false;
				_clockToShoot.restart();
			}
		}
	}

	void ReSpawn()
	{
		_isAlive = true;
	}
};


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

class enemy
{
	Texture _enemyTextureIdle;
	Texture _enemyTexturePointing;
	Texture _enemyTextureShooting;
	Sprite _enemySprite;
	bool _isAlive, _isVisible, _isShooting;
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

	enemy()
	{
		_enemyTextureIdle.loadFromFile("cowboy_idle.png");
		_enemyTexturePointing.loadFromFile("cowboy_pointing.png");
		_enemyTextureShooting.loadFromFile("cowboy_shooting.png");

		_enemySprite.setTexture(_enemyTextureIdle);
		_enemySprite.setScale(5, 5);
		_isAlive = true;
		_isVisible = false;
		_timeVisible = 2;
		_timeInvisible = 3;
		_isShooting = false;
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
		FloatRect bounds = _enemySprite.getGlobalBounds();
		return (bounds.contains(crosshairPosition.x, crosshairPosition.y));
	}

	void Destroy()
	{
		_isAlive = false;
	}

	void Draw(RenderWindow *wnd)
	{
		wnd->draw(_enemySprite);
	}

	void Update(RenderWindow *wnd)
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
				if (rand() % 100 > 5)
				{
					_isVisible = true;
					_enemySprite.setPosition(_RandomPos());
				}
			}
		}
		else
		{
			if (_clockToShoot.getElapsedTime().asSeconds() > 1.9)
			{
				_enemySprite.setTexture(_enemyTextureShooting);
				_isShooting = true;
			}
			else
			{
				if (_clockToShoot.getElapsedTime().asSeconds() > 1.5)
				{
					_enemySprite.setTexture(_enemyTexturePointing);
				}
			}

			if (_clockToShoot.getElapsedTime().asSeconds() > _timeVisible)
			{
				_isVisible = false;
				_isShooting = false;
				_enemySprite.setTexture(_enemyTextureIdle);
				_clockToShoot.restart();
			}
		}
	}

	void ReSpawn()
	{
		_isAlive = true;
	}

	bool CheckShoot()
	{
		return(_isShooting);
	}

	void StopShootig()
	{
		_isShooting = false;
		_isVisible = false;
	}
};


#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "crosshair.h"
#include "enemy.h"
#include "villager.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>

#include <thread>
#include <chrono>

using namespace sf;

class game
{
private:

	RenderWindow *_wnd;
	crosshair *_crosshair;
	enemy *_enemys;
	villager* _villagers;

	int _auxVillagers;
	
	Texture _backgroundTexture;
	Sprite _backgroundSprite;

	Text _livesText;
	int _lives;
	Texture _heartTexture;
	Sprite _heartSprite;

	Text _scoreText;
	int _score, _scoreAux;

	Text _gameoverText;

	Font _myFont;

	void _UpdateScore()
	{
		_scoreText.setString(std::to_string(_score));
	}

	void _Updatelives()
	{
		_livesText.setString(std::to_string(_lives));
	}

public:

	game()
	{
		_wnd = new RenderWindow(VideoMode(560, 640), "Integrador");
		_crosshair = new crosshair;
		_enemys = new enemy[4];
		_villagers = new villager[2];

		_auxVillagers = 0;

		_backgroundTexture.loadFromFile("background.png");
		_backgroundSprite.setTexture(_backgroundTexture);
		_backgroundSprite.setScale(5, 5);

		_myFont.loadFromFile("arial.ttf");

		_score = 0;
		_scoreAux = 0;
		_scoreText.setPosition(15, 560);
		_scoreText.setFillColor(sf::Color::White);
		_scoreText.setFont(_myFont);

		_heartTexture.loadFromFile("lives.png");
		_heartSprite.setTexture(_heartTexture);
		_heartSprite.setPosition(200, 575);
		_heartSprite.setScale(5, 5);
		_livesText.setPosition(280, 560);
		_livesText.setFillColor(sf::Color::White);
		_livesText.setFont(_myFont);
		_lives = 3;

		_gameoverText.setPosition(110, 150);
		_gameoverText.setScale(2, 2);
		_gameoverText.setFillColor(sf::Color::Red);
		_gameoverText.setFont(_myFont);
		_gameoverText.setString("GAME OVER");
		
		_UpdateScore();
		_Updatelives();
	}

	void Loop()
	{
		while (_wnd->isOpen())
		{
			ProcessEvents();
			Update();
			Draw();
		}
	}

	void ProcessEvents()
	{
		Event evt;
		while (_wnd->pollEvent(evt))
		{
			switch (evt.type)
			{
			case Event::Closed:
				_wnd->close();
				break;
			case Event::MouseMoved:
				_crosshair->SetPosition(evt.mouseMove.x, evt.mouseMove.y);
				break;
			case Event::MouseButtonPressed:
				if (evt.mouseButton.button == Mouse::Button::Left)
				{
					Shoot();
				}
				break;
			}
		}
	}

	void Update()
	{
		for (int i = 0; i < 4; i++)
		{
			_enemys[i].Update(_wnd);

			if (_enemys[i].CheckShoot())
			{
				_enemys[i].StopShootig();
				_lives-=1;
				_Updatelives();
			}
		}

		for (int i = 0; i < 2; i++)
		{
			_villagers[i].Update(_wnd);
		}
	}

	void Draw()
	{
		_wnd->clear();

		_wnd->draw(_backgroundSprite);

		for (int i = 0; i < 4; i++)
		{
			if (_enemys[i].IsActive())
			{
				_enemys[i].Draw(_wnd);
			}
		}

		for (int i = 0; i < 2; i++)
		{
			if (_villagers[i].IsActive())
			{
				_villagers[i].Draw(_wnd);
			}
		}

		_wnd->draw(_scoreText);

		_wnd->draw(_livesText);
		_wnd->draw(_heartSprite);

		if (_lives <= 0)
		{
			_wnd->draw(_gameoverText);
		}

		_crosshair->Draw(_wnd);

		_wnd->display();
	}

	void Shoot()
	{
		for (int i = 0; i < 4; i++)
		{
			if (_enemys[i].IsActive())
			{
				if (_enemys[i].WasShooted(_crosshair->GetPosition()))
				{
					_enemys[i].Destroy();
					_score++;
					_scoreAux++;
					if (_scoreAux == 4)
					{
						_scoreAux = 0;
						for (int i = 0; i < 4; i++)
						{
							_enemys[i].ReSpawn();
						}
					}
				}
			}
		}

		for (int i = 0; i < 2; i++)
		{
			if (_villagers[i].IsActive())
			{
				if (_villagers[i].WasShooted(_crosshair->GetPosition()))
				{
					_villagers[i].Destroy();
					_lives-=1;
					_auxVillagers++;
					if (_auxVillagers == 2)
					{
						_scoreAux = 0;
						for (int i = 0; i < 2; i++)
						{
							_villagers[i].ReSpawn();
						}
					}
				}
			}
		}

		_UpdateScore();
	}

	~game()
	{
		delete _enemys;
		delete _crosshair;
		delete _wnd;
	}
};
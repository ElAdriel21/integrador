#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class crosshair
{
	Texture _crosshairTexture;
	Sprite _crosshairSprite;

public:

	crosshair()
	{
		_crosshairTexture.loadFromFile("crosshair.png");
		_crosshairSprite.setTexture(_crosshairTexture);
		_crosshairSprite.setScale(5, 5);
	}

	void Draw(RenderWindow *wnd)
	{
		wnd->draw(_crosshairSprite);
	}

	void SetPosition(float x, float y)
	{
		_crosshairSprite.setPosition(x, y);
	}

	Vector2f GetPosition()
	{
		return(_crosshairSprite.getPosition());
	}
};


#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
using namespace sf;
using namespace std;


class Button
{
	int x1, x2, y1, y2;
public:
	Button() { x1 = x2 = y1 = y2 = 0; }
	Button(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

	void set(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}

	bool ispressed(Vector2i p)
	{
		return p.x >= x1 && p.x < x2
			&&p.y >= y1 && p.y <= y2;
	}
};
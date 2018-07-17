#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <cmath>
using namespace sf;
using namespace std;


// 709 x 106
class Animation : public sf::Drawable, public sf::Transformable
{
public:
	Animation(const string& picture);
	Animation(const string& picture, float x, float width, float high);
	void load(const string& picture, float x, float width, float high);
	void load(const string& picture);
	void update(sf::Time dt);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	float x1, x2, y1, y2;
	Time frame;
	VertexArray m_vertices;
	Texture m_texture;
};
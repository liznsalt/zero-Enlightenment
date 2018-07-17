#include "Power.h"


Power::Power():
	speed(500)
{
	m_vertices[0].position = Vector2f(10, 400);
	m_vertices[1].position = Vector2f(20, 400);
	m_vertices[2].position = Vector2f(20, 410);
	m_vertices[3].position = Vector2f(10, 410);

	m_texture.loadFromFile("power/normal.png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(10, 0);
	m_vertices[2].texCoords = Vector2f(10, 10);
	m_vertices[3].texCoords = Vector2f(0, 10);
}

//!!!!!!!!!!!
void Power::load(const string& picture, float x,float y, int direction)
{
	speed *= direction;

	move(Vector2f(x - getPosition().x, y - getPosition().y));

	m_vertices[0].position = Vector2f(x,y);
	m_vertices[1].position = Vector2f(x + 10, y);
	m_vertices[2].position = Vector2f(x + 10, y+10);
	m_vertices[3].position = Vector2f(x, y+10);

	m_texture.loadFromFile("power/" + picture + ".png");

	//cout << "Ok\n" << getPosition().x << endl;

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(10, 0);
	m_vertices[2].texCoords = Vector2f(10, 10);
	m_vertices[3].texCoords = Vector2f(0, 10);

	setOrigin(Vector2f(x - 10, y-400));
}

void Power::update(Time dt)
{
	Vector2f movement(0.f,0.f);
	movement.x += speed;
	move(movement * dt.asSeconds());
	//cout << "x:" << getPosition().x << endl;
}
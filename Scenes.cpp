#include "Scenes.h"

Scenes::Scenes() 
{
	m_vertices[0].position = Vector2f(0, 0);
	m_vertices[1].position = Vector2f(2560, 0);
	m_vertices[2].position = Vector2f(2560, 512);
	m_vertices[3].position = Vector2f(0, 512);

	m_texture.loadFromFile("scenes/battle.png");
	
	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(2560, 0);
	m_vertices[2].texCoords = Vector2f(2560, 512);
	m_vertices[3].texCoords = Vector2f(0, 512);
}

//tubiao
void Scenes::load(const string & p, int i)
{
	m_vertices[0].position = Vector2f(0, 0);
	m_vertices[1].position = Vector2f(20, 0);
	m_vertices[2].position = Vector2f(20, 20);
	m_vertices[3].position = Vector2f(0, 20);

	m_texture.loadFromFile("scenes/" + p + ".png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(100, 0);
	m_vertices[2].texCoords = Vector2f(100, 100);
	m_vertices[3].texCoords = Vector2f(0, 100);
}

void Scenes::load(const string &p)
{
	m_vertices[0].position = Vector2f(0, 0);
	m_vertices[1].position = Vector2f(2560, 0);
	m_vertices[2].position = Vector2f(2560, 512);
	m_vertices[3].position = Vector2f(0, 512);

	m_texture.loadFromFile("scenes/" + p + ".png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(2560, 0);
	m_vertices[2].texCoords = Vector2f(2560, 512);
	m_vertices[3].texCoords = Vector2f(0, 512);
}

void Scenes::load(const string& bg, float width, float high)
{
	m_vertices[0].position = Vector2f(0, 0);
	m_vertices[1].position = Vector2f(640, 0);
	m_vertices[2].position = Vector2f(640, 512);
	m_vertices[3].position = Vector2f(0, 512);

	m_texture.loadFromFile("scenes/" + bg + ".png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(width, 0);
	m_vertices[2].texCoords = Vector2f(width, high);
	m_vertices[3].texCoords = Vector2f(0, high);
}
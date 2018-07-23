#include "../Include/Menu.h"

Menu::Menu() 
{
	m_vertices[0].position = Vector2f(0, 0);
	m_vertices[1].position = Vector2f(200, 0);
	m_vertices[2].position = Vector2f(200, 320);
	m_vertices[3].position = Vector2f(0, 320);

	m_texture.loadFromFile("Media/menu/menu.png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(200, 0);
	m_vertices[2].texCoords = Vector2f(200, 320);
	m_vertices[3].texCoords = Vector2f(0, 320);
}


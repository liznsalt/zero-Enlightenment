#include "../Include/EasyPerson.h"

EasyPerson::EasyPerson()
{
	isMovingLeft = false;
	isMovingRight = false;
	isMovingUp = false;
	isMovingDown = false;

	m_vertices[0].position = Vector2f(0, 0);
	m_vertices[1].position = Vector2f(20, 0);
	m_vertices[2].position = Vector2f(20, 20);
	m_vertices[3].position = Vector2f(0, 20);

	m_texture.loadFromFile("Media/easyperson.png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(100, 0);
	m_vertices[2].texCoords = Vector2f(100, 100);
	m_vertices[3].texCoords = Vector2f(0, 100);
}

void EasyPerson::update(Time dt)
{
	Vector2f movement(0, 0);

	if (isMovingDown)
		movement.y += 10;
	if (isMovingUp)
		movement.y -= 10;
	if (isMovingLeft)
		movement.x -= 10;
	if (isMovingRight)
		movement.x += 10;

	move(movement * dt.asSeconds());
}

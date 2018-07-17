#include "Animation.h"

Animation::Animation(const string& picture):
	frame(seconds(1.f / 1.f)), 
	m_vertices(Quads, 4),
	x1(0), x2(709/6.0),
	y1(0), y2(106)
{
	m_vertices[0].position = Vector2f(10, 330);
	m_vertices[1].position = Vector2f(80, 330);
	m_vertices[2].position = Vector2f(80, 454);
	m_vertices[3].position = Vector2f(10, 454);

	m_texture.loadFromFile("animation/" + picture + ".png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(709/6.0, 0);
	m_vertices[2].texCoords = Vector2f(709/6.0, 106);
	m_vertices[3].texCoords = Vector2f(0, 106);
	
}

Animation::Animation(const string& picture, float x, float width, float high)
{
	m_vertices[0].position = Vector2f(x, 454 - high);
	m_vertices[1].position = Vector2f(x + width, 454 - high);
	m_vertices[2].position = Vector2f(x + width, 454);
	m_vertices[3].position = Vector2f(x, 454);

	m_texture.loadFromFile("animation/" + picture + ".png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(709 / 6.0, 0);
	m_vertices[2].texCoords = Vector2f(709 / 6.0, 106);
	m_vertices[3].texCoords = Vector2f(0, 106);
}

void Animation::load(const string& picture, float x, float width, float high)
{
	m_vertices[0].position = Vector2f(x, 454 - high);
	m_vertices[1].position = Vector2f(x + width, 454 - high);
	m_vertices[2].position = Vector2f(x + width, 454);
	m_vertices[3].position = Vector2f(x, 454);

	m_texture.loadFromFile("animation/" + picture + ".png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(709 / 6.0, 0);
	m_vertices[2].texCoords = Vector2f(709 / 6.0, 106);
	m_vertices[3].texCoords = Vector2f(0, 106);
}

void Animation::load(const string& picture)
{
	m_texture.loadFromFile("animation/" + picture + ".png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(709 / 6.0, 0);
	m_vertices[2].texCoords = Vector2f(709 / 6.0, 106);
	m_vertices[3].texCoords = Vector2f(0, 106);
}

void Animation::update(Time dt)
{
	Clock clock;
	float xx = 709/6.0, yy = 106;
	while (dt > seconds(0))
	{
		dt -= frame;
		x1 += xx; x2 += xx;

		if (x1 >= 709/6.0*6)
		{
			x1 = 0;
			x2 = 709/6.0;
		}
	}

	//cout << x1 << " " << x2 <<" "<< clock.restart().asSeconds() << endl;
	m_vertices[0].texCoords = Vector2f(x1, y1);
	m_vertices[1].texCoords = Vector2f(x2, y1);
	m_vertices[2].texCoords = Vector2f(x2 , y2);
	m_vertices[3].texCoords = Vector2f(x1, y2);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!注意注意注意注意注意!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//sleep(seconds(0.006));
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_vertices, states);
}
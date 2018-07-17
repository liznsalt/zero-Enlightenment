#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

//»ù´¡±³¾°Àà
class BaseScene :
	public Drawable,
	public Transformable
{
	
public:
	BaseScene();
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &m_texture;
		target.draw(m_vertices, states);
	}

	VertexArray m_vertices;
	Texture m_texture;
};
#pragma once
#include "BasePerson.h"
using namespace sf;
using namespace std;

class EasyPerson :
	public BasePerson
{

public:
	EasyPerson();
	void update(Time dt);

	bool isMovingLeft,
		isMovingRight,
		isMovingUp,
		isMovingDown;


private:

	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &m_texture;
		target.draw(m_vertices, states);
	}

	VertexArray m_vertices;
	Texture m_texture;
};
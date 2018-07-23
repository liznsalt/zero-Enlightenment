#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include "Power.h"
#include "Person.h"
using namespace sf;
using namespace std;


//払移議窃。。。。。。。
class Boss :
	public Drawable,
	public Transformable
{
public:
	int HP, ATK;
	bool face_to_right;
	bool isMovingLeft, isMovingRight, isJumping;
	bool canAtack;
	float foot_position;
	float speed, jump_speed;

	Boss();
	void load(const string& p);


	void remoteAtack();
	vector<Power> Remote;
	void gethurt(int atk)
	{
		HP -= atk;
	}

	
	void Shift();

	void update(Time dt);

private:
	Clock clock;
	Time timeSinceLastUpdate;
	Time atack_frame;

	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &m_texture;
		target.draw(m_vertices, states);
	}

	VertexArray m_vertices;
	Texture m_texture;
};

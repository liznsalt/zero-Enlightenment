#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

//����������
class BasePerson :
	public Drawable,
	public Transformable
{

public:

	//����
	virtual void update(Time dt) = 0;

	//�滭����Ļ��
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;

};
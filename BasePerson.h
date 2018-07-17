#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

//基础人物类
class BasePerson :
	public Drawable,
	public Transformable
{

public:

	//更新
	virtual void update(Time dt) = 0;

	//绘画再屏幕上
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;

};
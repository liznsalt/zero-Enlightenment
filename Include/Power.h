#pragma once
#include "BaseScene.h"
using namespace sf;
using namespace std;

class Power:
	public BaseScene
{
public:
	Power();
	void load(const string& picture, float x,float y, int direction);
	void update(Time dt);

private:
	float speed;
};
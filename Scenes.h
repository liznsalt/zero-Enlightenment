#pragma once 
#include "BaseScene.h"
using namespace sf;
using namespace std;

class Scenes:
	public BaseScene
{
public:
	Scenes();
	void load(const string& p);
	void load(const string& p, int i);
	void load(const string& bg, float width, float high);

};
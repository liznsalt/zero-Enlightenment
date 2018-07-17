#pragma once
#include <string>
using namespace std;


class Prop
{
	
public:
	int cnt;
	string name;
	string discribe;
	int value;
	Prop() 
	{
		cnt = 0;
		value = 0;
		name = "ÎŞÃèÊö";
		discribe = "ÎŞÃèÊö";
	}

	void set(string a, string b, int v)
	{
		cnt = 1;
		value = v;
		name = a;
		discribe = b;
	}

};
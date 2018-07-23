#pragma once
#include <string>
#include <vector>
#include "Prop.h"
using namespace std;

class Inventory
{
public:

	vector<Prop> self;

	void add(Prop& p)
	{
		auto it = self.begin();
		for (; it != self.end(); it++)
		{
			if (it->name == p.name)
				it->cnt++;
		}
		if (it == self.end())
		{
			self.push_back(p);
		}
	}

	void sub(Prop& p)
	{
		auto it = self.begin();
		for (; it != self.end(); it++)
		{
			if (it->name == p.name)
				it->cnt--;
		}
	}

	int cnt(string name)
	{
		auto it = self.begin();
		for (; it != self.end(); it++)
		{
			if (it->name == name)
				return it->cnt;
		}
		if (it == self.end())
			return 0;
	}

};
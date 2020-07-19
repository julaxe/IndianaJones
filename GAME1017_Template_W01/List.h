#pragma once
#include <vector>
#include "Sprite.h"
#include <iostream>
class List {
public:
	List() {}
	~List() {}
	void Render()
	{
		for (int i = 0; i < list.size(); i++)
		{
			list[i]->Render();
		}
	}
	void Update()
	{
		for (int i = 0; i < list.size(); i++)
		{
			list[i]->Update();
		}
	}
	void HandleEvents()
	{
		for (int i = 0; i < list.size(); i++)
		{
			list[i]->HandleEvents();
		}
	}

	std::vector<Sprite*>& getList() { return list; }
private:
	std::vector<Sprite*> list;

};
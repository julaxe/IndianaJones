#pragma once
#include "Sprite.h"
#include<vector>

class Display {
public:
	static Display* Instance() {
		if (m_Instance == nullptr) {
			m_Instance = new Display();
		}
		return m_Instance;
	}
	std::vector<Sprite*> &getList() { return list; }
	void Add(Sprite* s) { list.push_back(s); }
private:
	std::vector<Sprite*> list;
	static Display* m_Instance;
	Display();
	~Display();
};
#pragma once
#include "Sprite.h"
#include "Label.h"
#include<vector>

class Display {
public:
	static Display* Instance() {
		if (m_Instance == nullptr) {
			m_Instance = new Display();
		}
		return m_Instance;
	}
	std::vector<Sprite*> &getList() { return listSprites; }
	std::vector<Label*> &getListLabels() { return listLabels; }
	std::vector<Label*>& getListEnd() { return listLabels; }
	void AddSprite(Sprite* s) { listSprites.push_back(s); }
private:
	std::vector<Sprite*> listSprites;
	std::vector<Label*> listLabels;
	static Display* m_Instance;
	Display();
	~Display();
};
#pragma once
#include <string>
#include "SDL.h"
class Frame {
public:
	Frame(std::string name,int x, int y, int w, int h) : m_name(name),m_X(x), m_Y(y), m_W(w), m_H(h) {}
	SDL_Rect* getSrc() { return new SDL_Rect({ m_X, m_Y, m_W, m_H }); }
	int m_X, m_Y, m_W, m_H;
	std::string m_name;
};

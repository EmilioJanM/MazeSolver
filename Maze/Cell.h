#pragma once
#include <iostream>
#include "SDL.h"

class Cell
{
public:
	Cell();
	Cell(int x, int y, int h, int w);
	~Cell();
	short int wall;
	bool arriba;
	bool checked;
	void render(SDL_Renderer* render);
private:
	SDL_Rect r;
};
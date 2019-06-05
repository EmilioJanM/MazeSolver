#include "Cell.h"

Cell::Cell()
{
	wall = false;
	checked = false;
}
Cell::Cell(int x, int y, int h, int w) {
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	checked = false;
	wall = true;
}
Cell::~Cell()
{
}

void Cell::render(SDL_Renderer* renderer)
{
	switch (wall)
	{
	case 0:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &r);
		break;
	case 1:
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &r);
		break;
	case 2:
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &r);
		break;
	case 4:
		SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
		SDL_RenderFillRect(renderer, &r);
		break;
	default:
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &r);
		break;
	}
}
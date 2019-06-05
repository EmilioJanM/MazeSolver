#include <iostream>
#include "SDL.h"
#include "MazeGenerator.h"

int main(int argc, char *argv[]) {
	SDL_Window* window = NULL;
	int w = 960;
	window = SDL_CreateWindow
	(
		"BRIUGET", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		w,
		w,
		SDL_WINDOW_SHOWN
	);

	// Setup renderer
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event windowEvent;

	MazeGenerator maze(w, 50);
	maze.generateMaze();

	int x = NULL, y = NULL;

	while (true)
	{



		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				break;
			}
			if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				maze.receiveInput(0 ,x, y);
			}
			else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
				maze.receiveInput(1, x, y);
			}
			if (windowEvent.type == SDL_KEYDOWN) {
				if (windowEvent.key.keysym.sym == SDLK_SPACE)
					maze.DijkstraMazeSolver();
			}
				
		}

		maze.draw(renderer);

		SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
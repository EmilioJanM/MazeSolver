#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Cell.h"
#include "SDL.h"

class MazeGenerator
{
public:
	MazeGenerator(int w, int cellWidth);
	~MazeGenerator();

	void generateMaze();
	void generateMaze2();
	void DijkstraMazeSolver();
	void draw(SDL_Renderer *renderer);
	void receiveInput(const bool button, const int x, const  int y);
private:
	int checkDijkstraCell();
	void changeDijkstraCell(int loop);
	short int lado = 0;
	int total_pasillos = 0;
	bool ponerEspacio = true;
	struct graphito {
		int a[2];
		Cell c;
	};
	struct int2 {
		int a[2];
	};
	std::vector<graphito> graph;
	std::vector<int> cellToCheck;
	struct path {
		std::vector<int> way;
		int index = 0;
	};
	std::list<path> possible_paths;
	graphito *init;
	graphito *finish;
	int where_in_Cell_check = 1;
	int Iinit;
	int Ifinish;
	bool finished;
	int w;
	int cell_w;
};

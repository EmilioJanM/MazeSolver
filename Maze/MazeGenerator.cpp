#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(int w, int cellWidth) : cell_w(cellWidth) {
	srand(time(NULL));
	finished = false;
	this->w = w / cell_w;
}

MazeGenerator::~MazeGenerator()
{
}

void MazeGenerator::generateMaze()
{
	for (size_t i = 0; i != w; i++)
	{
		for (size_t j = 0; j != w; j++)
		{
			Cell c(j * cell_w, i * cell_w, cell_w, cell_w);
			graphito newG;
			if (!ponerEspacio) {
				if (i == 0 || j == 0) {
					c.wall = false;
				}
				else {
					if (!graph[graph.size() - 1].c.wall && !graph[graph.size() - w].c.wall && !graph[graph.size() - w - 1].c.wall) {
						c.wall = true;
						newG.c = c;
						newG.a[0] = i;
						newG.a[1] = j;
						graph.push_back(newG);
						continue;
					}
					else if (!graph[graph.size() - 1].c.wall && !graph[graph.size() - w].c.wall) {
						c.wall = false;
						total_pasillos++;
						newG.c = c;
						newG.a[0] = i;
						newG.a[1] = j;
						graph.push_back(newG);
						ponerEspacio = true;
						continue;
					}
					else if (graph[graph.size() - 1].c.wall && graph[graph.size() - w].c.wall && graph[graph.size() - w - 1].c.wall) {
						c.wall = false;
						total_pasillos++;
						newG.c = c;
						newG.a[0] = i;
						newG.a[1] = j;
						graph.push_back(newG);
						continue;
					}
					else if (graph[graph.size() - 1].c.wall && graph[graph.size() - w].c.wall) {
						c.wall = true;
						newG.c = c;
						newG.a[0] = i;
						newG.a[1] = j;
						graph.push_back(newG);
						if (rand() % 10 + 1 < 5)
							ponerEspacio = true;
						continue;
					}
					else if (graph[graph.size() - 1].c.wall || graph[graph.size() - w].c.wall) {
						if (rand() % 10 + 1 < 8) {
							c.wall = false;
							total_pasillos++;
						}
						else
							c.wall = true;
					}
				}
			}
			else {
				c.wall = true;
				newG.c = c;
				newG.a[0] = i;
				newG.a[1] = j;
				graph.push_back(newG);
				ponerEspacio = false;
				continue;
			}
			newG.c = c;
			newG.a[0] = i;
			newG.a[1] = j;
			graph.push_back(newG);
			ponerEspacio = false;
		}
	}
}
void MazeGenerator::generateMaze2()
{
	for (size_t i = 0; i != w; i++)
	{
		for (size_t j = 0; j != w; j++)
		{
			Cell c(i * cell_w, j * cell_w, cell_w, cell_w);
			graphito newG;
			if (!ponerEspacio) {
				if (i == 0 || j == 0) {
					c.wall = false;
				}
				else {
					if (graph[graph.size() - 1].c.wall && graph[graph.size() - w].c.wall) {
						c.wall = true;
						if (rand() % 10 + 1 < 6)
							c.arriba = false;
						else
							c.arriba = false;
						if (rand() % 20 + 1 < 17)
							ponerEspacio = true;
					}
					else if (graph[graph.size() - w].c.wall && graph[graph.size() - w].c.arriba) {
						c.wall = true;
						if (rand() % 10 + 1 < 8)
							c.arriba = true;
						else
							c.arriba = false;
						if (rand() % 20 + 1 < 17)
							ponerEspacio = true;
					}
					else if (graph[graph.size() -1].c.wall && !graph[graph.size() - 1].c.arriba) {
						c.wall = true;
						if (rand() % 10 + 1 < 8)
							c.arriba = false;
						else
							c.arriba = true;
						if (rand() % 20 + 1 < 17)
							ponerEspacio = true;
					}
				}

			}
			newG.c = c;
			newG.a[0] = i;
			newG.a[1] = j;
			graph.push_back(newG);
			ponerEspacio = false;
		}
	}
}
void MazeGenerator::DijkstraMazeSolver() {
	int loop = checkDijkstraCell();
	changeDijkstraCell(loop);
}

int MazeGenerator::checkDijkstraCell()
{
	int ret = cellToCheck.size();
	int sides = 0;
	for (size_t i = 0; i != ret; i++)
	{ 
		int index = cellToCheck[i];
		if (index - 1 != -1 && (graph[index - 1].c.wall == 0 || graph[index - 1].c.wall == 3)) {
			cellToCheck.push_back(index - 1);
			sides++;
		}
		if (index + 1 != w && (graph[index + 1].c.wall == 0 || graph[index + 1].c.wall == 3)) {
			cellToCheck.push_back(index + 1);
			sides++;
		}
		if (index - w > 0 && (graph[index - w].c.wall == 0 || graph[index - w].c.wall == 3)) {
			cellToCheck.push_back(index - w);
			sides++;
		}
		if (index + w < graph.size() && (graph[index + w].c.wall == 0 || graph[index + w].c.wall == 3)) {
			cellToCheck.push_back(index + w);
			sides++;
		}
	}
	return ret;
}
void MazeGenerator::changeDijkstraCell(int loop)
{
	for (size_t i = where_in_Cell_check; i != cellToCheck.size(); i++)
	{
		int index = cellToCheck[i];
		if (graph[index].c.wall == 3) {
			finished = true;
			break;
		}
		else if (graph[index].c.wall == 0) {
			graph[index].c.wall = 4;
			where_in_Cell_check++;
		}
		total_pasillos--;
	}
}

void MazeGenerator::draw(SDL_Renderer *renderer)
{
	for (size_t i = 0; i != graph.size(); i++)
	{
		graph[i].c.render(renderer);
	}
}

void MazeGenerator::receiveInput(const bool button ,const int x,const  int y)
{
	int index = (y / cell_w) * w + x / cell_w;
	if (button) {
		if (!graph[index].c.wall) {
			if (finish == NULL) {
				graph[index].c.wall = 3;
				finish = &graph[index];
			}
			else {
				finish->c.wall = 0;
				graph[index].c.wall = 3;
				finish = &graph[index];
			}
		}
	}
	else {
		if (!graph[index].c.wall) {
			if (init == NULL) {
				graph[index].c.wall = 2;
				init = &graph[index];
				Iinit = index;
				cellToCheck.push_back(index);
			}
			else {
				init->c.wall = 0;
				graph[index].c.wall = 2;
				init = &graph[index];
				cellToCheck.clear();
				cellToCheck.push_back(index);
			}
		}
	}
}


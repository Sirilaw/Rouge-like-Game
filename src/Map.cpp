#include "Map.h"
#include <stdlib.h>
#include <vector>

using namespace std;

Map::Map()
{
	srand(time(0));
	int tp;
	int row = 0, column = 0;
	vector<int> r;
	vector<int> c;
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 20; j++) {
			tp = rand() % 3 + 1;
			gmap[i][j] = new Grid(i + 1, j + 1, tp);
		}
	}
	for (int times = 0; times < barrier_num; times++) {
		row = rand() % 20;
		column = rand() % 30;
		for (int i = 0; i < c.size(); i++) {
			if (c[i] == column) {
				column = rand() % 30;
			}
		}
		c.push_back(column);
		for (int i = 0; i < r.size(); i++) {
			if (r[i] == row) {
				row = rand() % 20;
			}
		}
		r.push_back(row);
		gmap[column][row]->type = 0;
	}
}

Map::~Map()
{}



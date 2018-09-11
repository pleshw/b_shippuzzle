#ifndef BSHIPP_GENERATOR_HPP
#define BSHIPP_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <vector> 

using namespace std;

struct Battle_map{
	int height;
	int width;
	int **grid; ///[y][x] = 0 for water; [y][x] > 0 for ship
	void clear(void);
	Battle_map(int width, int height);
	void place_a_ship(int x, int y, int size, char direction);///place a ship of the selected size in the selected direction if its possible
	bool have_space_at(int x, int y, int size, char direction);///Return true if you can place a ship of selected size in the selected direction at the position
};



class Map_gen{
private:
	vector<Battle_map> All_maps;
public:
	void new_map(int width, int height);
	void save(void);
};



#endif
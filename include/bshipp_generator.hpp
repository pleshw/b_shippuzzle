#ifndef BSHIPP_GENERATOR_HPP
#define BSHIPP_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <vector> 

using namespace std;

struct Boat{
	char id;
	int  size;
	Boat(char id, int size);
};

struct Battle_map{
	
	int height;
	int width;
	char **grid; ///w for water
	
	void place_a_ship(int x, int y, Boat vessel, char direction);///place a ship of the selected size in the selected direction if its possible
	bool have_space_at(int x, int y, Boat vessel, char direction);///Return true if you can place a ship of selected size in the selected direction at the position

	Battle_map(int width, int height);
	~Battle_map();
};



class Map_generator{
private:
	vector<Battle_map> Map_list;

public:
	void new_map(int width, int height);
	void view_last(void);
};



#endif
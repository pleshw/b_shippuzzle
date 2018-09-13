#ifndef BSHIPP_GENERATOR_HPP
#define BSHIPP_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <vector> 
#include <iomanip>

using namespace std;

struct Boat{
	char id;
	unsigned int size;
	Boat(char id, unsigned int size);
};

struct Battle_map{
	
	unsigned long height;
	unsigned long  width;
	char          **grid; ///w for water //b for border //id for boat
	
	void place_a_ship(unsigned int x, unsigned int y,       Boat & vessel, char direction);///place a ship of the selected size in the selected direction if its possible
	bool in_map_range(unsigned int x, unsigned int y, unsigned int size, char direction);///Return true if you can place a ship of selected size in the selected direction at the position

	Battle_map(unsigned long const width, unsigned long const height);
	~Battle_map();
};

ostream& operator<<( std::ostream& os, const Battle_map & mapa );

class Map_generator{
private:
	vector<Battle_map> Map_list;

public:
	void new_map(unsigned long const width, unsigned long const height);
	void view_last(void);
};



#endif
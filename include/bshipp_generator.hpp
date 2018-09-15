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

struct Coords{
	int x;
	int y;
	Coords(unsigned int x = 999, unsigned int y = 999);
};
ostream& operator<<( std::ostream& os, const Coords & coordenada );

struct Boat{
	char id;
	unsigned int size;
	Coords position;
	Boat(char id, unsigned int size);
};



struct Battle_map{
	unsigned long       height;
	unsigned long        width;
	char                **grid; ///w for water //. for border //id for boat
	vector<Coords>  Free_spots;
	vector<Boat>     Ship_list;

	void place_a_ship  (unsigned int x, unsigned int y,     Boat & vessel, char direction);///place a ship of the selected size in the selected direction if its possible
	bool in_map_range  (unsigned int x, unsigned int y, unsigned int size, char direction);///Return true if you can place a ship of selected size in the selected direction at the position
	bool free_position (unsigned int x, unsigned int y, unsigned int size, char direction);

	Battle_map(unsigned long const width, unsigned long const height);
	~Battle_map();
};
ostream& operator<<( std::ostream& os, const Battle_map & mapa );



class Map_generator{
public:
	vector<Battle_map> Map_list;
	ofstream          save_file;

	void   new_map(unsigned long const width, unsigned long const height);
	void view_last(void);
	void  save_all(void);
};



#endif
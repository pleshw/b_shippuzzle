#include "../include/BattleMap.h"



//initialize the grid of the map
void BattleMap::init( void )
{
	//resize to width and height
	grid.resize( height, std::vector<char>(width));

	//fill
	for (unsigned int y(0); y < height; y++)
		for (unsigned int x(0); x < width; x++)
			grid[y][x] = '~';
}

//get the width
size_t BattleMap::getWidth ( void ) const
{
	return width;
}

//get the height
size_t BattleMap::getHeight ( void ) const
{
	return height;
}

//get a element giving a position as a pos2d
char BattleMap::getElement ( pos2d pos ) const
{
	return grid[pos.y][pos.x];
}

//get a vector with all water spots in the grid
Map BattleMap::getFreeSpots( void ) const
{
	Map tmp; //create a temporary Map
	//fill tmp with the water cordinates
	for (unsigned int y(0); y < height; y++)
		for (unsigned int x(0); x < width; x++)
			if(grid[y][x] == '~') tmp.emplace_back( x, y ); // if water
	return tmp;
}

int main()
{
	BattleMap bm( 15, 15);

	std::cout << std::endl << bm << std::endl;

	return 0;
}
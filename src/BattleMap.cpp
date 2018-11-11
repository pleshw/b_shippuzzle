#include "../include/BattleMap.h"


//initialize the grid of the map
void BattleMap::init( void )
{
	//resize to width and height
	grid.resize( height, std::vector<std::string>(width));

	//fill
	for (unsigned int y(0); y < height; y++)
		for (unsigned int x(0); x < width; x++)
			grid[y][x] = "~";
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

//get a vector with all water spots in the grid
Map BattleMap::getFreeSpots( void ) const
{
	Map tmp; //create a temporary Map
	//fill tmp with the water cordinates
	for (unsigned int y(0); y < height; y++)
		for (unsigned int x(0); x < width; x++)
			if(isWater(pos2d(x, y))) tmp.emplace_back( x, y );
	return tmp;
}

//get a element giving a position as a pos2d
std::string BattleMap::getElement ( pos2d pos ) const
{
	return grid[pos.y][pos.x];
}

//verify if a position has water -- if not ship or border
bool BattleMap::isWater ( pos2d pos ) const
{
	return isMap(pos) and grid[pos.y][pos.x] == "~";
}

//verify if a position has a ship -- if not water or border
bool BattleMap::isShip ( pos2d pos ) const
{
	return isMap(pos) and !isWater(pos) and !isBorder(pos);
}

//verify if the position has a border -- if not water or ship
bool BattleMap::isBorder ( pos2d pos ) const
{
	return isMap(pos) and grid[pos.y][pos.x] == ".";
}

//verify if a position is inner map scope
bool BattleMap::isMap ( pos2d pos ) const
{
	return (size_t)pos.x < width and (size_t)pos.x >= 0 and (size_t)pos.y < height and (size_t)pos.y >= 0;
}

//check if have space to a ship
bool BattleMap::haveSpace ( size_t size, pos2d pos, Direction direction )  const
{
	for(unsigned int i(0); i < size; i++)
	{
		if(direction == Direction::HORIZONTAL)
			if ( !isWater( pos2d( pos.x+i, pos.y ) ) ) return false;

		if(direction == Direction::VERTICAL)
			if ( !isWater( pos2d( pos.x, pos.y+i ) ) ) return false;
	}
	return true;
}

//verify if have space for a ship place it
bool BattleMap::setShip ( Ship ship, pos2d pos, Direction direction )
{
	if (!haveSpace( ship.size, pos, direction )) return false;

	for(unsigned int i(0); i < ship.size; i++)
	{
		if(direction == Direction::HORIZONTAL)
			grid[pos.y][pos.x+i] = ship.id; 

		if(direction == Direction::VERTICAL)
			grid[pos.y+i][pos.x] = ship.id;
	}
	return true;
}



int main()
{
	BattleMap bm(15, 15);
	std::cout << std::endl << bm << std::endl;

	Ship Submarine  ( "s",  1, "Submarine" );
	Ship BattleShip ( "BS", 5, "Battle Ship" );

	bm.setShip ( BattleShip, pos2d(0, 0),   Direction::VERTICAL );
	bm.setShip ( BattleShip, pos2d(1, 0),   Direction::HORIZONTAL );
	bm.setShip ( Submarine,  pos2d(14, 14), Direction::VERTICAL );

	std::cout << std::endl << bm << std::endl;

	return 0;
}
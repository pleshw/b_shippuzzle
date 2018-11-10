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
char BattleMap::getElement ( pos2d pos ) const
{
	return grid[pos.y][pos.x];
}

//verify if a position has water -- if not ship or border
bool BattleMap::isWater ( pos2d pos ) const
{
	return (!isShip(pos) or !isBorder(pos)) and isMap(pos);
}

//verify if a position has a ship -- if not water or border
bool BattleMap::isShip ( pos2d pos ) const
{
	return (!isWater(pos) or !isBorder(pos)) and isMap(pos);
}

//verify if the position has a border -- if not water or ship
bool BattleMap::isBorder ( pos2d pos ) const
{
	return (!isWater(pos) or !isShip(pos)) and isMap(pos);
}

//verify if a position is inner map scope
bool BattleMap::isMap ( pos2d pos ) const
{
	return (size_t)pos.x < width and (size_t)pos.x >= 0 and  (size_t)pos.y < height and (size_t)pos.y >= 0;
}

//check if have space to a ship
bool BattleMap::haveSpace ( Ship ship )  const
{
	pos2d shipPosition(ship.position.x, ship.position.y);
	for(unsigned int i(0); i < ship.size; i++)
	{
		if(ship.direction::HORIZONTAL)
			if (!isWater(shipPosition.x + i)) return false;

		if(ship.direction::VERTICAL)
			if (!isWater( shipPosition.y + i )) return false;		
	}
	return true;
}

//verify if have space for a ship place it
bool BattleMap::setShip ( Ship ship )
{
	if (!haveSpace(ship)) return false;
	return true;
}
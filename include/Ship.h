#ifndef _BATTLESHIP_SHIP
#define _BATTLESHIP_SHIP

#include "Position.h"
#include <iostream>
#include <vector>


struct Ship
{
	char       id;
	size_t     size;
	pos2d      position;

	enum class direction { VERTICAL = 0, HORIZONTAL };

	Ship( char _id = '~', size_t _size = 1) 
		: id         ( _id ),
		  size       ( _size )
		{/*EMPTY*/}
};

using fleet = std::vector<Ship>;


#endif
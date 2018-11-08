#ifndef _BATTLESHIP_SHIP
#define _BATTLESHIP_SHIP

#include "Position.h"
#include <iostream>
#include <vector>


struct Ship{
	char    id;
	size_t  size;
	pos2d  position;
	Ship( char _id = '~', size_t _size = 1) 
		: id    ( _id ),
		  size  ( _size )
		{/*EMPTY*/}

	std::ostream &operator << ( std::ostream &os, const Ship &s );
};

using fleet = std::vector<Ship>;


#endif
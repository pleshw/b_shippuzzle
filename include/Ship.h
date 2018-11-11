#ifndef _BATTLESHIP_SHIP
#define _BATTLESHIP_SHIP

#include "Position.h"
#include <iostream>
#include <vector>


struct Ship
{
	std::string  id;
	size_t       size;
	std::string  name;

	Ship( std::string _id = "~", size_t _size = 1, std::string _name = "Ship") 
		: id         ( _id ),
		  size       ( _size ),
		  name       ( _name )
		{/*EMPTY*/}
};

using Fleet = std::vector<Ship>;


#endif
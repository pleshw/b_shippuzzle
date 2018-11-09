#ifndef _BATTLESHIP_COORDINATES
#define _BATTLESHIP_COORDINATES

#include <iostream>
#include <vector> 


struct pos2d
{
	int x;
	int y;
	pos2d( int _x = 0,  int _y = 0)
		: x ( _x ),
		  y ( _y )
		{/*EMPTY*/}

	friend std::ostream &operator << ( std::ostream &os, const pos2d &p )
		{ os << p.x << " " << p.y; return os; }
};

using Map = std::vector<pos2d>;


#endif
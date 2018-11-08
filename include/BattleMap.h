#ifndef _BATTLESHIP_BATTLEMAP
#define _BATTLESHIP_BATTLEMAP

#include "Position.h"
#include "Ship.h"
#include <iostream>
#include <vector>

using grid = std::vector<vector<char>>;

struct BattleMap{
	public:
		BattleMap( const size_t _width = 15, const size_t _height = 15 )
			: width  ( _width ),
			  height ( _height )
			{ init(); }

		const Map    getFreeSpots ( void );
		std::ostream &operator << ( std::ostream& os, const BattleMap &bm );

	private:
		size_t   height;
		size_t   width;
		grid     sea;
		fleet    ships;

		inline void init        ( void );
		void        setShip     ( void );
		void        setFleet    ( fleet f );
		char        getElement  ( pos2d pos );
};

using GameSet = std::vector<BattleMap>;


#endif
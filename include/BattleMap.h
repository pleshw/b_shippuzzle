#ifndef _BATTLESHIP_BATTLEMAP
#define _BATTLESHIP_BATTLEMAP

#include "Position.h"
#include "Ship.h"
#include <iostream>
#include <vector>

using Grid = std::vector<std::vector<char>>;

class BattleMap{
	private:
		size_t width;
		size_t height;
		Grid   grid;
		fleet  ships;
		void init  ( void );

	public:
		BattleMap( const size_t _width = 15, const size_t _height = 15 )
			: width  ( _width ),
			  height ( _height )
			{ init(); }

		size_t  getWidth     ( void )      const;
		size_t  getHeight    ( void )      const;
		char    getElement   ( pos2d pos ) const;
		Map     getFreeSpots ( void )      const;

		friend std::ostream &operator << ( std::ostream &os, const BattleMap &bm );
};

using GameSet = std::vector<BattleMap>;

#endif
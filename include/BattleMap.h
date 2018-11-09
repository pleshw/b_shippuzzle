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
		
		fleet  ships;
		void init  ( void );

	public:
		Grid   grid;
		BattleMap( const size_t _width = 15, const size_t _height = 15 )
			: width  ( _width ),
			  height ( _height )
			{ init(); }

		size_t  getWidth     ( void )      const;
		size_t  getHeight    ( void )      const;
		char    getElement   ( pos2d pos ) const;
		Map     getFreeSpots ( void )      const;

		friend std::ostream &operator << ( std::ostream &os, const BattleMap &bm )
		{ 
			std::string str;
			for (unsigned int y(0); y < bm.height; y++){
				for (unsigned int x(0); x < bm.width; x++){
					str += bm.grid[y][x];
					str += " ";
				}
				str += '\n';
			}
			os << str;
			return os;				
		}
};

using GameSet = std::vector<BattleMap>;

#endif
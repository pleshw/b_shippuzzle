#ifndef _BATTLESHIP_BATTLEMAP
#define _BATTLESHIP_BATTLEMAP

#include "Position.h"
#include "Ship.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>

using Grid = std::vector<std::vector<std::string>>;

class BattleMap{
	private:
		size_t width;
		size_t height;
		Grid   grid;
		Fleet  ships;
		void init  ( void );

	public:
		BattleMap( const size_t _width = 15, const size_t _height = 15 )
			: width  ( _width ),
			  height ( _height )
			{ init(); }

		size_t      getWidth      ( void ) const;
		size_t      getHeight     ( void ) const;
		Map         getFreeSpots  ( void ) const;
		std::string getElement    ( pos2d pos ) const;
		bool        isWater       ( pos2d pos ) const;
		bool        isShip        ( pos2d pos ) const;
		bool        isBorder      ( pos2d pos ) const;
		bool        isMap         ( pos2d pos ) const;
		bool        haveSpace     ( size_t size, pos2d position, Direction direction ) const;

		bool setShip    ( Ship ship, pos2d position, Direction direction );
		void setBorder  ( pos2d pos );
		void setFleet   ( const Fleet &fleet, const Map &map, const Compass &compass );

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
#ifndef _BATTLESHIP_MAPGENERATOR
#define _BATTLESHIP_MAPGENERATOR

#include "BattleMap.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class MapGenerator{
	public:
		GameSet        maplist;
		std::ofstream  saveFile;
		Map            freeSpots;

		void          newMap       ( size_t width, size_t height );
		BattleMap     viewLast     ( void );
		void          getAll       ( void );
		void          saveLast     ( void );
		void          saveAll      ( void );
		void          removeLast   ( void );
		void          removeAll    ( void );
		std::ostream  &operator << ( std::ostream &os, const MapGenerator &mg ); //show all maps

	private:
		bool  isWater        ( pos2d pos, unsigned int size, char direction );
		bool  isShip         ( pos2d pos );
		bool  isFreePosition ( pos2d pos );
		bool  haveSpace      ( size_t size, char direction );
		void  setShip        ( pos2d pos, Ship & ship, char direction );
		void  setBorder      ( pos2d pos );
};

#endif
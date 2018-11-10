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
		void      newMap      ( size_t width, size_t height, Fleet fleet ); //create a new map in mapList
		BattleMap getMap      ( size_t selector ) const;       //get map [selector] from mapList
		BattleMap getFirst    ( void )            const;       //get the first map from mapList
		BattleMap getLast     ( void )            const;       //get the last map from mapList
		GameSet   getMapList  ( void )            const;       //get the actual mapList
		void      saveMap     ( size_t selector );             //save map [selector] from mapList in saveFile
		void      saveFirst   ( void );                        //save the first map from mapList in saveFile
		void      saveLast    ( void );                        //save the last map from mapList in saveFile
		void      saveAll     ( void );	                       //save all maps from mapList in saveFile
		void      removeLast  ( void );                        //remove last from mapList
		void      removeAll   ( void );                        //remove all from mapList
		
	private:
		GameSet        mapList;
		std::ofstream  saveFile;
		Map            freeSpots;
};

#endif
#ifndef _BATTLESHIP_GAME
#define _BATTLESHIP_GAME

#include "BattleMap.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


class Game
{
	private:
		BattleMap ActualMap;

	public:
		Game( BattleMap _actualMap)
			: ActualMap ( _actualMap )
			{/*EMPTY*/}
		void      setMap   ( unsigned int n );
		Grid      getMap   ( void );
		void      shoot    ( pos2d pos );
		bool      hit      ( pos2d pos );	
		const Map display  ( void );
};


#endif
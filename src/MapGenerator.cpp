#include "../include/MapGenerator.h"

MapGenerator::MapGenerator ( void )
{
	try
	{
		saveFile.open("maps.txt");
	}
	catch (std::ofstream::failure &error) 
	{
		std::cerr << std::endl << error 
				  << std::endl;
	}
	if (!saveFile || !saveFile.good() || !saveFile.open())
		std::cout << "ERROR: Unable to write in file, you are unable to save.";
	else saveFileReady = true;
}

MapGenerator::MapGenerator ( std::string _src )
{
	try
	{
		saveFile.open(_src);
	}
	catch (std::ofstream::failure &error) 
	{
		std::cerr << std::endl << error 
				  << std::endl;
	}
	if (!saveFile || !saveFile.good() || !saveFile.open())
		std::cout << "ERROR: Unable to write in file, you are unable to save.";
	else saveFileReady = true;
}


BattleMap MapGenerator::getMap ( size_t selector ) const
{
	return mapList[selector];
}

BattleMap MapGenerator::getFirst ( void ) const
{
	return mapList[0];
} 

BattleMap MapGenerator::getLast ( void ) const
{
	return mapList[mapList.size() - 1];
} 

GameSet MapGenerator::getMapList ( void ) const
{
	return mapList;
} 

void MapGenerator::saveMap ( size_t selector )
{
	if (!saveFileReady) return; // i will make a exception later 
	saveFile >> mapList.getMap(selector); // remember: try to overload the operator >> for maps.
}




























int main()
{
	BattleMap bm(15, 15);
	std::cout << std::endl << bm << std::endl;

	Ship Submarine  ( "s",  1, "Submarine" );
	Ship BattleShip ( "S", 3, "Battle Ship" );

	Fleet   f;
	Map     m;
	Compass c;

	for(auto i(0); i < 12; i++)
	{
		if (i%2 == 0)
		{
			f.push_back    ( Submarine );
			m.emplace_back ( i, 12 - i );
			c.push_back    ( Direction::VERTICAL );
		}else
		{
			f.push_back    ( BattleShip );
			m.emplace_back ( 12 - i, i );
			c.push_back    ( Direction::HORIZONTAL );
		}
	}

	bm.setFleet(f, m, c);

	for(const pos2d &posi : bm.getFreeSpots()) //para cada Ship (como unit) em fleet
	{
		std::cout << std::endl << "Free spot at " << posi << std::endl;
	}

	std::cout << std::endl << bm << std::endl;

	return 0;
}
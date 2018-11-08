#include "bshipp_generator.hpp"
#include <sstream>

class Map_reader
{
	public:
		vector<Battle_map>   Map_list;
		ifstream             Maps_file;

		Map_reader( std::string _src = "mapas.txt" ) :
			Maps_file(_src)
			{/*EMPTY*/}

		void create_maps ( void );
		void shoot       ( Coords pos );
		bool hit         ( Coords pos );

		std::vector<Coords> getSpots ( void );
};
#include "bshipp_generator.hpp"

class Map_reader{
	public:
	vector<Battle_map> Map_list;
	ifstream          Maps_file;

	void create_map(int selector);

}
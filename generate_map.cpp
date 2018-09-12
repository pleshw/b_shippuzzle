#include <iostream>
#include "include/bshipp_generator.hpp"

using namespace std;

int main(){
	
	Boat Battle_ship('S', 4), Cruiser('c', 3), Destroyer('d', 2), Submarine('s', 1);

	Map_generator generator;

	generator.new_map(15, 15);

	generator.view_last();

	return 0;
}
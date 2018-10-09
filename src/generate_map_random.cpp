#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "../include/bshipp_generator.hpp"
#include <fstream>

using namespace std;


void place_random(Battle_map & Map, Boat & ship, unsigned int amount);

int main(int argc, char const *argv[]){
	
	unsigned int map_size = 15;

	if(argc > 2) map_size = atoi(argv[2]);

	if (argc < 1){
		cout << endl << endl << "Please set the number of maps as first arg.";
		exit(-1);
	}

	//criando barcos que vão ser usados	
	Boat Battle_ship('S', 4), Cruiser('C', 3), Destroyer('D', 2), Submarine('s', 1);

	//creating a new map generator
	Map_generator generator;

	//positioning the squad at random places
	for(int i(0); i < atoi(argv[1]); i++){
		//create a new map
		generator.new_map(map_size, map_size);
		
		//set a new seed
		srand (time(NULL)+i);

		//place the ship in a random spot
		place_random(generator.Map_list[i], Battle_ship, 1);
		place_random(generator.Map_list[i],     Cruiser, 2);
		place_random(generator.Map_list[i],   Destroyer, 3);
		place_random(generator.Map_list[i],   Submarine, 4);
	}

	generator.view_all();

	generator.save_all();

	return 0;
}




void place_random(Battle_map & Map, Boat & ship, unsigned int amount){
	int  _random   = rand() % Map.Free_spots.size();//random number in free spot vector
	int  _posX     = Map.Free_spots[_random].x;//x of the free spot selected position
	int  _posY     = Map.Free_spots[_random].y;//y of the free spot selected position
	int  _dir_seed = rand() % 1;//flip a coin to get direction
	char _dir;//direction
	if(_dir_seed == 0) _dir = 'h';
	if(_dir_seed == 1) _dir = 'v';	

	for(unsigned int j(0); j < amount; j++){
		while(!Map.free_position(_posX, _posY, ship.size, _dir)){
			_random   = rand() % Map.Free_spots.size();
			_posX     = Map.Free_spots[_random].x;
			_posY     = Map.Free_spots[_random].y;
			_dir_seed = rand() % 1;
			if(_dir_seed == 0) _dir = 'h';
			if(_dir_seed == 1) _dir = 'v';	
		}

		Map.place_a_ship(_posX, _posY, ship, _dir);
	}
}

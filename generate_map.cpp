#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "include/bshipp_generator.hpp"
#include <fstream>

using namespace std;

int main(){
	
	//criando barcos que vão ser usados	
	Boat Battle_ship('S', 4), Cruiser('C', 3), Destroyer('D', 2), Submarine('s', 1);

	//criando objeto da classe geradora de mapas
	Map_generator generator;

	//criando um novo mapa
	generator.new_map(15, 15);

	srand (time(NULL));
	
	int  _random   = rand() % generator.Map_list.back().Free_spots.size();
	int  _posX     = generator.Map_list.back().Free_spots[_random].x;
	int  _posY     = generator.Map_list.back().Free_spots[_random].y;
	int  _dir_seed = rand() % 1;
	char _dir;
	if(_dir_seed == 0) _dir = 'h';
	if(_dir_seed == 1) _dir = 'v';

	for(unsigned int i(0); i < 1; i++){
		while(!generator.Map_list.back().free_position(_posX, _posY, Battle_ship.size, _dir)){
			_random   = rand() % generator.Map_list.back().Free_spots.size();
			_posX     = generator.Map_list.back().Free_spots[_random].x;
			_posY     = generator.Map_list.back().Free_spots[_random].y;
			_dir_seed = rand() % 1;
			if(_dir_seed == 0) _dir = 'h';
			if(_dir_seed == 1) _dir = 'v';	
		}

		generator.Map_list.back().place_a_ship(_posX, _posY, Battle_ship, _dir);
	}

	for(unsigned int i(0); i < 4; i++){
		while(!generator.Map_list.back().free_position(_posX, _posY, Submarine.size, _dir)){
			_random   = rand() % generator.Map_list.back().Free_spots.size();
			_posX     = generator.Map_list.back().Free_spots[_random].x;
			_posY     = generator.Map_list.back().Free_spots[_random].y;
			_dir_seed = rand() % 1;
			if(_dir_seed == 0) _dir = 'h';
			if(_dir_seed == 1) _dir = 'v';	
		}

		generator.Map_list.back().place_a_ship(_posX, _posY, Submarine, _dir);
	}


	for(unsigned int i(0); i < 3; i++){
		while(!generator.Map_list.back().free_position(_posX, _posY, Cruiser.size, _dir)){
			_random   = rand() % generator.Map_list.back().Free_spots.size();
			_posX     = generator.Map_list.back().Free_spots[_random].x;
			_posY     = generator.Map_list.back().Free_spots[_random].y;
			_dir_seed = rand() % 1;
			if(_dir_seed == 0) _dir = 'h';
			if(_dir_seed == 1) _dir = 'v';	
		}

		generator.Map_list.back().place_a_ship(_posX, _posY, Cruiser, _dir);
	}

	for(unsigned int i(0); i < 2; i++){
		while(!generator.Map_list.back().free_position(_posX, _posY, Destroyer.size, _dir)){
			_random   = rand() % generator.Map_list.back().Free_spots.size();
			_posX     = generator.Map_list.back().Free_spots[_random].x;
			_posY     = generator.Map_list.back().Free_spots[_random].y;
			_dir_seed = rand() % 1;
			if(_dir_seed == 0) _dir = 'h';
			if(_dir_seed == 1) _dir = 'v';	
		}

		generator.Map_list.back().place_a_ship(_posX, _posY, Destroyer, _dir);
	}

	ofstream arquivo("mapas.txt");

	for (unsigned int i(0); i < generator.Map_list.back().height; i++){
		for (unsigned int j(0); j < generator.Map_list.back().width; j++){
			arquivo << generator.Map_list.back().grid[i][j];
		}
		arquivo << endl;
	}

	arquivo.close();

	generator.view_last();

	return 0;
}





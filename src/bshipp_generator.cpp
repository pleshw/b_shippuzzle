#include "../include/bshipp_generator.hpp"

//Battle_map functions and constructor
Battle_map::Battle_map(int width, int height){
	this->width  = width;
	this->height = height;
	this->grid = (int**) malloc (height * sizeof(int*));
	for(int i(0); i < height; i++){
		this->grid[i] = (int*) malloc (width * sizeof(int));
	}
	//filling grid with water
	for(int i(0); i < height; i++){
		for(int j(0); j < width; j++){
			this->grid[i][j] = 0;
		}
	}
}

void Battle_map::clear(void){
	for(int i(0); i < this->height; i++){
			delete [] this->grid[i];
	}
	delete [] this->grid;
}

void Battle_map::place_a_ship(int x, int y, int size, char direction){
	if (this->have_space_at(x, y, size, direction)){
		for(int n(0); n < size; n++){
			switch(direction){
				case 'h':
					for(auto n(0); n < size; n++) this->grid[y][x+n] = n+1; 
					break;
				case 'v':
					for(auto n(0); n < size; n++) this->grid[y+n][x] = n+1; 
					break;
			}
		}
	}
}

bool Battle_map::have_space_at(int x, int y, int size, char direction){
	if (x >= this->width || x < this->width) return false;
	if (y >= this->height || y < this->height) return false;

	switch(direction){
		case 'h':
			if((x+size) >= this->width || (x+size) < this->width) return false;
			break;
		case 'v':
			if((y+size) >= this->height || (y+size) < this->height) return false;
			break;
	}
	return true;
}


//Map_gen functions

void Map_gen::new_map(int width, int height){

	Battle_map tmp_map(width, height);

	this->All_maps.insert(tmp_map);
	
	for(int i(0); i < this->All_maps.back().height; i++){
		for(int j(0); j < this->All_maps.back().width; j++){
			cout << this->All_maps.back().grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}





void Map_gen::save(){

}
#include "../include/bshipp_generator.hpp"
//Boat functions and constructor
Boat::Boat(char id){
	if (id != 'b'){
		this->id = id;
	}else{
		cout << "nao pode";
	}
}


//Battle_map functions and constructor
Battle_map::Battle_map(int width, int height){
	this->width  = width;
	this->height = height;
	this->grid = (char**) malloc (height * sizeof(char*));
	for(int i(0); i < height; i++){
		this->grid[i] = (char*) malloc (width * sizeof(char));
	}
	//filling grid with water
	for(int i(0); i < height; i++){
		for(int j(0); j < width; j++){
			this->grid[i][j] = 'w';
		}
	}
}

void Battle_map::clear(void){
	for(int i(0); i < this->height; i++){
			delete [] this->grid[i];
	}
	delete [] this->grid;
}

void Battle_map::place_a_ship(int x, int y, Boat cockboat, char direction){
	if (this->have_space_at(x, y, cockboat, direction)){
		for(int n(0); n < cockboat.size; n++){
			switch(direction){
				case 'h':
					for(auto n(0); n < size; n++){
						this->grid[y][x+n] = cockboat.id;
					}
					break;
				case 'v':
					for(auto n(0); n < size; n++){
						this->grid[y+n][x] = cockboat.id;
					}
					break;
			}
		}
	}
}

bool Battle_map::have_space_at(int x, int y, Boat cockboat, char direction){
	// if is after or before the map border
	if (x >= this->width || x < this->width) return false;
	if (y >= this->height || y < this->height) return false;

	// if the size doesn't fit
	switch(direction){
		case 'h':
			if((x+size) >= this->width || (x+size) < this->width) return false;
			break;
		case 'v':
			if((y+size) >= this->height || (y+size) < this->height) return false;
			break;
	}

	//if there's a boat around
	if (){
		/* code */
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
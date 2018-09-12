#include "../include/bshipp_generator.hpp"
//Boat functions and constructor
Boat::Boat(char id, int size){
	this->id   = id;
	this->size = size;
}

//Battle_map functions and constructor
Battle_map::Battle_map(int width, int height){
	//get the dimensions
	this->width  = width;
	this->height = height;
	
	//allocate grid
	this->grid = new char*[height];
	for(int i(0); i < height; i++){
		this->grid[i] = new char(width);
	}

	//filling grid with water
	for(int i(0); i < height; i++){
		for(int j(0); j < width; j++){
			this->grid[i][j] = 'w';
		}
	}
}
//delete the memory allocated for the map
Battle_map::~Battle_map(){
	for(int i(0); i < this->height; i++){
		delete [] this->grid[i];
	}
	delete [] this->grid;
}



//place a ship in a position
void Battle_map::place_a_ship(int x, int y, Boat vessel, char direction){
	switch(direction){
		case 'h':
		//draw boat
			this->grid[y-1][x-1] = 'b';
			this->grid[y]  [x-1] = 'b';
			this->grid[y+1][x-1] = 'b';

			this->grid[y-1][x+vessel.size] = 'b';
			this->grid[y]  [x+vessel.size] = 'b';
			this->grid[y+1][x+vessel.size] = 'b';

			for(auto n(0); n < vessel.size; n++){
				this->grid[y+1][x+n] = 'b'; //border
				this->grid[y]  [x+n] = vessel.id;
				this->grid[y-1][x+n] = 'b';
			}
		break;
	
		case 'v':
		//draw boat
			this->grid[y-1][x-1] = 'b';
			this->grid[y-1][x] = 'b';
			this->grid[y-1][x+1] = 'b';

			this->grid[y+vessel.size][x-1] = 'b';
			this->grid[y+vessel.size][x] = 'b';
			this->grid[y+vessel.size][x+1] = 'b';

			for(auto n(0); n < vessel.size; n++){
				this->grid[y+n][x+1] = 'b'; //border
				this->grid[y+n][x] = vessel.id;
				this->grid[y+n][x-1] = 'b'; //border
			}
		break;

		default:
		//draw boat
			this->grid[y-1][x-1] = 'b';
			this->grid[y]  [x-1] = 'b';
			this->grid[y+1][x-1] = 'b';

			this->grid[y-1][x+vessel.size] = 'b';
			this->grid[y]  [x+vessel.size] = 'b';
			this->grid[y+1][x+vessel.size] = 'b';
			for(auto n(0); n < vessel.size; n++){
				this->grid[y][x+n] = vessel.id;
			}			
		break;
	}
}

//verify if a ship can be placed in that position
bool Battle_map::have_space_at(int x, int y, Boat vessel, char direction){
	// if is after or before the map border
	if (x >= this->width || x < this->width) return false;
	if (y >= this->height || y < this->height) return false;

	// if the size doesn't fit
	switch(direction){
		case 'h':
		if((x+vessel.size) >= this->width || (x+vessel.size) < this->width) return false;
		break;
		case 'v':
		if((y+vessel.size) >= this->height || (y+vessel.size) < this->height) return false;
		break;
	}


	return true;
}


//Map_generator functions
void Map_generator::new_map(int width, int height){
	Map_list.emplace_back(width, height);
}

void Map_generator::view_last(void){
	cout << endl;
	for(int i(0); i < this->Map_list.back().height; i++){
		for(int j(0); j < this->Map_list.back().width; j++){
			cout << this->Map_list.back().grid[i][j] << " ";
		}
		cout << endl;
	}
}
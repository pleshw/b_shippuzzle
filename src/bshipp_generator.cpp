#include "../include/bshipp_generator.hpp"
/////-------------------------------------------------------------Boat functions and constructor
Boat::Boat(char id, unsigned int size){
	this->id   = id;
	this->size = size;
}

/////--------------------------------------------------------------Battle_map functions and constructor
Battle_map::Battle_map(unsigned long width, unsigned long height){
	//get the dimensions
	this->width  = width;
	this->height = height;
	
	//allocate grid
	this->grid = new char*[height];
	for(unsigned long i(0); i < height; i++){
		this->grid[i] = new char(width);
	}

	//filling grid with water
	for(unsigned long i(0); i < height; i++){
		for(unsigned long j(0); j < width; j++){
			this->grid[i][j] = 'w';
		}
	}
}
//delete the memory allocated for the map
Battle_map::~Battle_map(){
	for(unsigned long i(0); i < this->height; i++){
		delete [] this->grid[i];
	}
	delete [] this->grid;
}
//place a ship in a position
void Battle_map::place_a_ship(unsigned int x, unsigned int y, Boat vessel, char direction){
	if (this->in_map_range(x, y, vessel.size, direction)){
		bool border_left   = false;
		bool border_top    = false;
		bool border_bottom = false;
		bool border_right  = false;



		if (border_left){
			cout << endl << endl << "BORDA NA ESQUERDA" << endl << endl;
		}
		if (border_top){
			cout << endl << endl << "BORDA NO TOPO" << endl << endl;
		}
		if (border_bottom){
			cout << endl << endl << "BORDA NO FUNDO" << endl << endl;
		}
		if (border_right){
			cout << endl << endl << "BORDA NA DIREITA" << endl << endl;
		}

		switch(direction){
			case 'h':
			//all border cases
				if (this->in_map_range(          x-1 ,  y  , 1 , 'h')) border_left   = true;
				if (this->in_map_range(            x , y-1 , 1 , 'h')) border_top    = true;
				if (this->in_map_range(            x , y+1 , 1 , 'h')) border_bottom = true;
				if (this->in_map_range(x+vessel.size ,  y  , 1 , 'h')) border_right  = true;

			//draw boat and border
				if(border_left && border_top)     this->grid[y-1][x-1] = 'b';
				if(border_left)                   this->grid[ y ][x-1] = 'b';
				if(border_left && border_bottom)  this->grid[y+1][x-1] = 'b';
				
				if(border_right && border_top)    this->grid[y-1][x+vessel.size] = 'b';
				if(border_right)                  this->grid[ y ][x+vessel.size] = 'b';
				if(border_right && border_bottom) this->grid[y+1][x+vessel.size] = 'b';

				for(unsigned int n(0); n < vessel.size; n++){
					if(border_bottom) this->grid[y+1][x+n] = 'b';
					if(border_top)    this->grid[y-1][x+n] = 'b';
					this->grid[y][x+n] = vessel.id;
				}
			break;
	
			case 'v':

			//all border cases
				if (this->in_map_range(x-1 ,             y , 1 , 'v')) border_left   = true;
				if (this->in_map_range( x  ,           y-1 , 1 , 'v')) border_top    = true;
				if (this->in_map_range( x  , y+vessel.size , 1 , 'v')) border_bottom = true;
				if (this->in_map_range(x+1 ,             y , 1 , 'v')) border_right  = true;

			//draw boat and border
				if(border_left && border_top)     this->grid[y-1][x-1] = 'b';
				if(border_top)                    this->grid[y-1][ x ] = 'b';
				if(border_right && border_top)    this->grid[y-1][x+1] = 'b';

				if(border_left && border_bottom)  this->grid[y+vessel.size][x-1] = 'b';
				if(border_bottom)                 this->grid[y+vessel.size][ x ] = 'b';
				if(border_right && border_bottom) this->grid[y+vessel.size][x+1] = 'b';
				
				for(unsigned int n(0); n < vessel.size; n++){
					if(border_right) this->grid[y+n][x+1] = 'b';
					if(border_left)  this->grid[y+n][x-1] = 'b';
					this->grid[y+n][x] = vessel.id;
				}
			break;
		}
	}
}
//verify if this position and this size still in the map range
bool Battle_map::in_map_range(unsigned int x, unsigned int y, unsigned int size, char direction){
	if (direction == 'h'){
		if(((x+size) <= this->width) && (y < this->height) && (x >= 0) && (y >= 0)){
			return true;
		}
	}
	if (direction == 'v'){
		if((x < this->width) && ((y+size) <= this->height) && (x >= 0) && (y >= 0)){
			return true;
		}
	}
	return false;
}


/////------------------------------------------------------------------------------Map_generator functions
void Map_generator::new_map(unsigned long const width, unsigned long const height){
	Boat Battle_ship ('S', 4);
	Boat Cruiser     ('C', 3);
	Boat Destroyer   ('D', 2);
	Boat Submarine   ('s', 1);

	Map_list.emplace_back(width, height);

	Map_list.back().place_a_ship(0, 0, Battle_ship, 'h');

	Map_list.back().place_a_ship(5, 1, Cruiser, 'v');
	// Map_list.back().place_a_ship(5, 1, Cruiser, 'v');

	// Map_list.back().place_a_ship(1, 7, Destroyer, 'h');
	// Map_list.back().place_a_ship(3, 7, Destroyer, 'h');
	// Map_list.back().place_a_ship(6, 7, Destroyer, 'h');

	// Map_list.back().place_a_ship(3, 10, Submarine, 'v');
	// Map_list.back().place_a_ship(4, 10, Submarine, 'v');
	// Map_list.back().place_a_ship(6, 10, Submarine, 'v');
	// Map_list.back().place_a_ship(8, 10, Submarine, 'v');
}

void Map_generator::view_last(void){
	cout << endl;
	for(unsigned long i(0); i < this->Map_list.back().height; i++){
		for(unsigned long j(0); j < this->Map_list.back().width; j++){
			cout << this->Map_list.back().grid[i][j] << " ";
		}
		cout << endl;
	}
}
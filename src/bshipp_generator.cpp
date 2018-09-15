#include "../include/bshipp_generator.hpp"

/////-------------------------------------------------------------SOBRECARGAS

//output battlemap
ostream& operator<< ( std::ostream& os, const Battle_map & mapa ){
	string printar;
	for (unsigned long i(0); i < mapa.height; i++){
		for (unsigned long j(0); j < mapa.width; j++){
			printar += mapa.grid[i][j];
			printar += " "; 
		}
		printar += "\n";
	}
	os << printar;
	return os;
}







/////--------------------------------------------------------------------------------------------------------
// CONSTRUCTORS AND DESTRUCTORS
Coords::Coords(unsigned int x, unsigned int y){
	this->x = x;
	this->y = y;
}

Boat::Boat(char id, unsigned int size){
	this->id   = id;
	this->size = size;
}


Battle_map::Battle_map(unsigned long width, unsigned long height){
	//get the dimensions
	this->width  = width;
	this->height = height;

	//allocate grid
	this->grid = new char*[height];
	for(unsigned long i(0); i < height; i++){
		this->grid[i] = new char(width);
		//filling with water
		for(unsigned long j(0); j < width; j++){
			this->grid[i][j] = '~';
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






//BATTLE MAP
void Battle_map::place_a_ship(unsigned int x, unsigned int y, Boat & vessel, char direction){
	// cout << endl << endl << "----------------------------" << endl
	// 	 << ">>place_a_ship log." << endl;

	// cout << "--Input details-- " << endl;
	// cout << "X: " << x << endl;
	// cout << "Y: " << y << endl;
	// cout << "Boat Size: " << vessel.size << endl;
	// cout << "Direction: " << direction << endl << endl;

	// cout << "--Map details-- " << endl;
	// cout << "With: "   << this->width  << endl;
	// cout << "Height: " << this->height << endl << endl;


	// cout << "--More details-- " << endl;
	// if (direction == 'h'){
	// 	cout << "From: " <<  x              << " " << y << endl;
	// 	cout << "To: "   << (x+vessel.size) << " " << y << endl << endl;
	// }

	// if (direction == 'v'){
	// 	cout << "From: " << x << " " <<  y              << endl;
	// 	cout << "To: "   << x << " " << (y+vessel.size) << endl << endl;
	// }


	if (this->in_map_range(x, y, vessel.size, direction)){
		bool border_left   = false;
		bool border_top    = false;
		bool border_bottom = false;
		bool border_right  = false;
		

		switch(direction){
			case 'h':
			//all border cases
				if (this->in_map_range(          x-1 ,  y  , 1 , 'h')) {border_left   = true;}
				if (this->in_map_range(            x , y-1 , 1 , 'h')) {border_top    = true;}
				if (this->in_map_range(            x , y+1 , 1 , 'h')) {border_bottom = true;}
				if (this->in_map_range(x+vessel.size ,  y  , 1 , 'h')) {border_right  = true;}

				
			//draw boat and border
				if(border_left && border_top)     {this->grid[y-1][x-1] = '.';}
				if(border_left)                   {this->grid[ y ][x-1] = '.';}
				if(border_left && border_bottom)  {this->grid[y+1][x-1] = '.';}
				
				if(border_right && border_top)    {this->grid[y-1][x+vessel.size] = '.';}
				if(border_right)                  {this->grid[ y ][x+vessel.size] = '.';}
				if(border_right && border_bottom) {this->grid[y+1][x+vessel.size] = '.';}

				for(unsigned int n(0); n < vessel.size; n++){
					if(border_bottom) {this->grid[y+1][x+n] = '.';}
					if(border_top)    {this->grid[y-1][x+n] = '.';}
					this->grid[y][x+n] = vessel.id;
				}
				// cout << endl << "SHIP PLACED IN POSITION >> " << x << " " << y << endl
				// 	 << "WITH DIRECTION '" << direction << "' AND SIZE " << vessel.size;

			//update free spots array	
			//update free spots array	
				for(unsigned int i(0); i < height; i++){
					for(unsigned int j(0); j < width; j++){
						if(this->free_position(j, i, 1, 'h')){
							this->Free_spots.emplace_back(i, j);
						}
					}
				}
				// cout << endl << "FREE SPOTS ARRAY UPDATED" << x << " " << y << endl << endl;
			break;
	
			case 'v':

			//all border cases
				if (this->in_map_range(x-1 ,             y , 1 , 'v')) {border_left   = true;}
				if (this->in_map_range( x  ,           y-1 , 1 , 'v')) {border_top    = true;}
				if (this->in_map_range( x  , y+vessel.size , 1 , 'v')) {border_bottom = true;}
				if (this->in_map_range(x+1 ,             y , 1 , 'v')) {border_right  = true;}

			//draw boat and border
				if(border_left && border_top)     {this->grid[y-1][x-1] = '.';}
				if(border_top)                    {this->grid[y-1][ x ] = '.';}
				if(border_right && border_top)    {this->grid[y-1][x+1] = '.';}

				if(border_left && border_bottom)  {this->grid[y+vessel.size][x-1] = '.';}
				if(border_bottom)                 {this->grid[y+vessel.size][ x ] = '.';}
				if(border_right && border_bottom) {this->grid[y+vessel.size][x+1] = '.';}
				
				for(unsigned int n(0); n < vessel.size; n++){
					if(border_right) {this->grid[y+n][x+1] = '.';}
					if(border_left)  {this->grid[y+n][x-1] = '.';}
					this->grid[y+n][x] = vessel.id;
				}
				// cout << endl << "SHIP PLACED IN POSITION >> " << x << " " << y << endl
				// 	 << "WITH DIRECTION " << direction << " AND SIZE " << vessel.size;

			//update free spots array	
				for(unsigned int i(0); i < height; i++){
					for(unsigned int j(0); j < width; j++){
						if(this->free_position(j, i, 1, 'h')){
							this->Free_spots.emplace_back(i, j);
						}
					}
				}
				// cout << endl << "FREE SPOTS ARRAY UPDATED" << x << " " << y << endl << endl;
			break;
		}
	}

	

}

//verify if this position and this size still in the map range
bool Battle_map::in_map_range(unsigned int x, unsigned int y, unsigned int size, char direction){

	// cout << endl << endl << "----------------------------" << endl
	// 	 << ">>in_map_range log." << endl;

	// cout << "--Input details-- " << endl;
	// cout << "X: " << x << endl;
	// cout << "Y: " << y << endl;
	// cout << "Size: " << size << endl;
	// cout << "Direction: " << direction << endl << endl;

	// cout << "--Map details-- " << endl;
	// cout << "With: " << this->width << endl;
	// cout << "Height: " << this->height << endl << endl;


	// cout << " --More details-- " << endl;
	// if (direction == 'h'){
	// 	cout << "From: " <<  x       << " " << y << endl;
	// 	cout << "To: "   << (x+size) << " " << y << endl << endl;
	// }

	// if (direction == 'v'){
	// 	cout << "From: " << x << " " <<  y << endl;
	// 	cout << "To: "   << x << " " << (y+size) << endl << endl;
	// }



	if (x >= this->width)  { return false; }
	if (y >= this->height) { return false; }
	if (x < 0)             { return false; }
	if (y < 0)             { return false; }

	if (direction == 'h'){
		if(((x+size) <= this->width)){
			// cout << endl << "Draw this" << endl;
			return true;
		}
	}
	if (direction == 'v'){
		if(((y+size) <= this->height)){
			// cout << endl << "Draw this" << endl;
			return true;
		}
	}
	return false;
}

//verify if the selected coord is a valid spot to place a boat with this size
bool Battle_map::free_position(unsigned int x, unsigned int y, unsigned int size, char direction){
	// cout << endl << endl << "----------------------------" << endl
	// 	 << ">>free_position log." << endl;

	// cout << "--Input details-- " << endl;
	// cout << "X: " << x << endl;
	// cout << "Y: " << y << endl;
	// cout << "Size: " << size << endl;
	// cout << "Direction: " << direction << endl << endl;

	// cout << "--Map details-- " << endl;
	// cout << "With: " << this->width << endl;
	// cout << "Height: " << this->height << endl << endl;


	// cout << " --More details-- " << endl;
	// if (direction == 'h'){
	// 	cout << "From: " <<  x       << " " << y << endl;
	// 	cout << "To: "   << (x+size) << " " << y << endl << endl;
	// }

	// if (direction == 'v'){
	// 	cout << "From: " << x << " " <<  y << endl;
	// 	cout << "To: "   << x << " " << (y+size) << endl << endl;
	// }

	// cout << "In this position: " << this->grid[y][x] << endl << endl;




	if (this->grid[y][x] != '~')                    return false;
	if (!this->in_map_range(x, y, size, direction))	return false;
	
	switch(direction){
		case 'h':
			for (unsigned int i(0); i < size; i++){
				if (this->grid[y][x+i] != '~'){
					// cout << endl << "------position " << x+i << " " << y << " is not water" << endl << endl; 
					return false;
				}
			}
		break;

		case 'v':
			for (unsigned int i(0); i < size; i++){
				if (this->grid[y+i][x] != '~'){
					// cout << endl << "------position " << x << " " << y+i << " is not water" << endl << endl;
					return false;
				}
			}
		break;

		default:
			return false;
		break;
	}

	return true;
}





/////MAP GENERATOR

void Map_generator::new_map(unsigned long width, unsigned long height){

	Map_list.emplace_back(width, height);

	for(unsigned int i(0); i < height; i++){
		for(unsigned int j(0); j < width; j++){
			if(this->Map_list.back().free_position(j, i, 1, 'h')){
				this->Map_list.back().Free_spots.emplace_back(i, j);
			}
		}
	}

	// cout << endl << endl << "MAP CREATED WITH SUCESS" << endl << endl;
}

void Map_generator::view_last(void){
	// cout << endl << endl << "----------------------------" << endl
	// 	 << ">>view_last log." << endl;

	// cout << endl << "Last Map info" << endl;
	// cout << "Width: "  << this->Map_list.back().width << endl;
	// cout << "Height: " << this->Map_list.back().width << endl;

	cout << this->Map_list.back();
}
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
//output coordenada
ostream& operator<< ( std::ostream& os, const Coords & coordenada ){
	os << coordenada.x << " " << coordenada.y;
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

	this->grid.resize(height);
	for(unsigned int i(0); i < height; i++){
		this->grid[i].resize(width);
	}
	
	//allocate grid
	for(unsigned int i(0); i < height; i++){
		for(unsigned int j(0); j < width; j++){
			this->grid[i][j] = '~';
		}
	}

	for(unsigned int i(0); i < height; i++){
		for(unsigned int j(0); j < width; j++){
			if(this->free_position(j, i, 1, 'h')){
				this->Free_spots.emplace_back(i, j);
			}
		}
	}
}


//BATTLE MAP
void Battle_map::place_a_ship(unsigned int x, unsigned int y, Boat & vessel, char direction){
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


			//update free spots array	
			//update free spots array	
				for(unsigned int i(0); i < height; i++){
					for(unsigned int j(0); j < width; j++){
						if(this->free_position(j, i, 1, 'h')){
							this->Free_spots.emplace_back(i, j);
						}
					}
				}
			//add to ship list
				vessel.position.x = x;
				vessel.position.y = y;
				this->Ship_list.push_back(vessel);
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

			//update free spots array	
				for(unsigned int i(0); i < height; i++){
					for(unsigned int j(0); j < width; j++){
						if(this->free_position(j, i, 1, 'h')){
							this->Free_spots.emplace_back(i, j);
						}
					}
				}
			//add to ship list
				vessel.position.x = x;
				vessel.position.y = y;
				this->Ship_list.push_back(vessel);				
			break;
		}
	}
}

//verify if this position and this size still in the map range
bool Battle_map::in_map_range(unsigned int x, unsigned int y, unsigned int size, char direction){
	if (x >= this->width)  { return false; }
	if (y >= this->height) { return false; }
	if (x < 0)             { return false; }
	if (y < 0)             { return false; }

	if (direction == 'h'){
		if(((x+size) <= this->width)){
			return true;
		}
	}
	if (direction == 'v'){
		if(((y+size) <= this->height)){
			return true;
		}
	}
	return false;
}

//verify if the selected coord is a valid spot to place a boat with this size
bool Battle_map::free_position(unsigned int x, unsigned int y, unsigned int size, char direction){
	if (this->grid[y][x] != '~')                    return false;
	if (!this->in_map_range(x, y, size, direction))	return false;
	
	switch(direction){
		case 'h':
			for (unsigned int i(0); i < size; i++){
				if (this->grid[y][x+i] != '~'){ 
					return false;
				}
			}
		break;

		case 'v':
			for (unsigned int i(0); i < size; i++){
				if (this->grid[y+i][x] != '~'){
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
}

void Map_generator::view_last(void){
	cout << endl << endl << this->Map_list.back() << endl;
}

void Map_generator::view_all(void){
	for(unsigned int i(0); i < this->Map_list.size(); i++){
		cout << endl << i+1;
		cout << endl << this->Map_list[i];
	}
}

void Map_generator::save_all(void){
	this->save_file.open("mapas.txt");
	this->save_file << this->Map_list.size() << " //number of maps";
	for(unsigned int i(0); i < this->Map_list.size(); i++){
		this->save_file << endl << "mapa: " << this->Map_list.back().width << " " << this->Map_list.back().height << endl;	
		for(unsigned int j(0); j < this->Map_list[i].Ship_list.size(); j++){
			this->save_file << "id: "   << this->Map_list[i].Ship_list[j].id       << ", ";
			this->save_file << "size: " << this->Map_list[i].Ship_list[j].size     << ", ";
			this->save_file << "pos: "  << this->Map_list[i].Ship_list[j].position << endl;
		}
		this->save_file << "-";//end of a map in the file
	}
	this->save_file.close();
}
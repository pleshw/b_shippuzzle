#include "../include/bshipp_reader.hpp"

void Map_reader::create_maps  ( void )
{
	std::string       linha;
	std::stringstream fluxo;
	size_t numero_de_mapas = 0;

	std::getline(Maps_file, linha);
	fluxo << linha;
	fluxo >> numero_de_mapas;

	std::cout << std::endl << std::endl << numero_de_mapas << std::endl << std::endl;

	std::string tmp;
	unsigned int tmp_width;
	unsigned int tmp_height;
	char         tmp_id;
	unsigned int tmp_size;
	Coords       tmp_pos;
	while(!Maps_file.eof()) 
	{
		cout << 21321;
		std::getline(Maps_file, linha);
		fluxo << linha;
		fluxo >> tmp;

		while(tmp != "-") {
			std::getline(Maps_file, linha);
			fluxo << linha;
			fluxo >> tmp;

			if ( tmp == "mapa:" )
			{
				fluxo >> tmp_width;
				fluxo >> tmp_height;
				std::cout << std::endl  << "Mapa de " << tmp_width << " " << tmp_height
						  << " criado." << std::endl;				
			}

			if ( tmp == "id:" )
			{
				fluxo >> tmp_id;
				fluxo >> tmp_size;
				fluxo >> tmp_pos.x;
				fluxo >> tmp_pos.y;
				std::cout << std::endl << "Barco de id "   << tmp_id << " e tamanho" << tmp_size
						  << " posicionado em " << tmp_pos << "." << std::endl;
			}
		}
	}
}


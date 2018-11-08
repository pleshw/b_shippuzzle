CC               = g++
CPPFLAGS         = -Wall -std=c++11 -pedantic -Wextra

GENERATOR        = gen_rand
PLAYER           = play

_MANDATORY_OBJS  = Position.o Ship.o BattleMap.o 
_PLAY_OBJS       = $(_MANDATORY_OBJS) Game.o
_GEN_OBJS        = $(_MANDATORY_OBJS) MapGenerator.o


build: $(_GEN_OBJS) $(_PLAY_OBJS)
	$(CC) $(_GEN_OBJS) -o $(GENERATOR)
	$(CC) $(_PLAY_OBJS) -o $(PLAYER)
	rm -rf build/*.o
	mv *.o build/
	./play

Position.o:
	$(CC) -c src/Position.cpp $(CPPFLAGS)

Ship.o: include/Position.h
	$(CC) -c src/Ship.cpp $(CPPFLAGS)

BattleMap.o: include/Position.h include/Ship.h
	$(CC) -c src/BattleMap.cpp $(CPPFLAGS)

MapGenerator.o: include/Position.h include/Ship.h include/BattleMap.h
	$(CC) -c src/MapGenerator.cpp $(CPPFLAGS)




bshipp_play.o: include/bshipp_reader.hpp
	$(CC) -c src/bshipp_play.cpp $(CPPFLAGS)

bshipp_reader.o: include/bshipp_generator.hpp
	$(CC) -c src/bshipp_reader.cpp $(CPPFLAGS)
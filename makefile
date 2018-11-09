CC               = g++
CPPFLAGS         = -Wall -std=c++11 -pedantic -Wextra

GENERATOR        = gen_rand
PLAYER           = play

_MANDATORY_OBJS  = BattleMap.o 
_PLAY_OBJS       = $(_MANDATORY_OBJS) Game.o
_GEN_OBJS        = $(_MANDATORY_OBJS) MapGenerator.o


build: $(_GEN_OBJS) $(_PLAY_OBJS)
	$(CC) $(_GEN_OBJS) -o $(GENERATOR)
	$(CC) $(_PLAY_OBJS) -o $(PLAYER)
	rm -rf build/*.o
	mv *.o build/
	./play

BattleMap.o: include/Position.h include/Ship.h
	$(CC) -c src/BattleMap.cpp $(CPPFLAGS)

MapGenerator.o: include/Position.h include/Ship.h include/BattleMap.h
	$(CC) -c src/MapGenerator.cpp $(CPPFLAGS)

Game.o: include/Position.h include/Ship.h include/BattleMap.h
	$(CC) -c src/Game.cpp $(CPPFLAGS)


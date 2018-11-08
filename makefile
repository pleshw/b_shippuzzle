CC              = g++
CPPFLAGS        = -Wall -std=c++11 -pedantic -Wextra
GENERATOR       = gen_rand
CONSOLE         = play
_GEN_OBJS       = generate_map_random.o bshipp_generator.o
_PLAY_OBJS      = bshipp_play.o bshipp_reader.o
_PLAY_EXTRAS    = bshipp_generator.o


build: $(_GEN_OBJS) $(_PLAY_OBJS)
	$(CC) $(_GEN_OBJS) -o $(GENERATOR)
	$(CC) $(_PLAY_EXTRAS) $(_PLAY_OBJS) -o $(CONSOLE)
	rm -rf build/*.o
	mv *.o build/
	./play

generate_map_random.o:
	$(CC) -c src/generate_map_random.cpp $(CPPFLAGS)

bshipp_generator.o: include/bshipp_generator.hpp
	$(CC) -c src/bshipp_generator.cpp $(CPPFLAGS)



bshipp_play.o: include/bshipp_reader.hpp
	$(CC) -c src/bshipp_play.cpp $(CPPFLAGS)

bshipp_reader.o: include/bshipp_generator.hpp
	$(CC) -c src/bshipp_reader.cpp $(CPPFLAGS)
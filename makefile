CC            = g++
CPPFLAGS      = -Wall -std=c++11
PROG          = bin/gen_rand
_ALL_OBJS     = generate_map_random.o bshipp_generator.o

build: $(_ALL_OBJS)
	$(CC) $(_ALL_OBJS) -o $(PROG)
	rm -rf build/*.o
	mv *.o build/

generate_map_random.o:
	$(CC) -c src/generate_map_random.cpp $(CPPFLAGS)

bshipp_generator.o: include/bshipp_generator.hpp
	$(CC) -c src/bshipp_generator.cpp $(CPPFLAGS)
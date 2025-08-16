SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)

all: bin/main

bin/main: $(OBJECTS)
	g++ $(OBJECTS) -o bin/main

obj/%.o: src/%.cpp
	g++ -Iinc -c $< -o $@

clean:
	rm -rf obj/*.o  bin/main

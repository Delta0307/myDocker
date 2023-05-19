all: main

INC := -I./include

./build/main.o: ./src/main.cpp
	g++ $(INC) -c ./src/main.cpp -o ./build/main.o

./build/Docker.o: ./src/Docker.cpp
	g++ $(INC) -c ./src/Docker.cpp -o ./build/Docker.o

main: ./build/main.o ./build/Docker.o
	g++ ./build/main.o ./build/Docker.o -o docker

clean:
	rm docker build/*.o

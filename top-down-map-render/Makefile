CC=clang++
CFLAGS=-Wall -pedantic -g -std=c++17
INCLUDE=`pkg-config sdl3 --cflags`
LIBS=`pkg-config sdl3 --libs`
OUT=top-down-map-render
SRC=./src/*.cpp

build:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) $(LIBS) -o $(OUT)

run:
	./$(OUT)

clean:
	rm $(OUT)

CC=clang++
CFLAGS=-Wall -pedantic -g -std=c++17
INCLUDE=-Isrc/
SRC=./src/*.cpp
OUT=ecs

build:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(OUT)

clean:
	rm ./$(OUT)

run:
	./$(OUT)

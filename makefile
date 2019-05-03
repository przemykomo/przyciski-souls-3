LIB_INCLUDE := -I/home/przemykomo/glfw/include/ -I./src/
LIB_PATH := -L/home/przemykomo/glfw/src/
LIB := -lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -lm

SRC_CPP := $(shell find src/ -name '*.cpp')

all:
	g++ $(SRC_CPP) -o ./bin/release/game $(LIB_INCLUDE) $(LIB_PATH) $(LIB) -lstdc++

run:
	./bin/release/game

test:
	g++ $(SRC_CPP) -o ./bin/release/game $(LIB_INCLUDE) $(LIB_PATH) $(LIB) -lstdc++
	./bin/release/game

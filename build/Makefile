build:
	g++ ../src/*.cpp -std=c++17 -Wall -g -I ../include -o ./game -I C:/raylib/raylib/src -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

no_console:
	g++ ../src/*.cpp -std=c++17 -Wall -g -I ../include -o ./game -I C:/raylib/raylib/src -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows

#add -mwindows to remove the console
run:
	./game.exe
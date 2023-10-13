SOURCEDIR=src/include/game

all:
	g++ -g -I src/include -L src/lib -o main main.cpp $(SOURCEDIR)/*.cpp $(SOURCEDIR)/Interfaces/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
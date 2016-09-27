#OBJS specifies which files to compile as part of project
OBJS = Main.cpp Game.cpp Tile.cpp Player.cpp Scene.cpp

#CC specifies the compiler
CC = g++

#COMILER_FLAGS specifies the additional compilation options
#-w suppresses all warnings
COMPILER_FLAGS = -w -std=gnu++0x

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

#OBJ_NAME specifies the name of the executable
OBJ_NAME = game

#compile the executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

OBJS = main.cc Vec2.cc UVCoords.cc Sprite.cc Batch.cc ShaderProgram.cc

CC = clang++

COMPILER_FLAGS = -w -v

LINKER_FLAGS = -lSDL2 -lGL -lGLEW -lSDL2_image -lSOIL

OBJ_NAME = main

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
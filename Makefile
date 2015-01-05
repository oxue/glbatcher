OBJS = main2.cc Vec2.cc UVCoords.cc Sprite.cc Batch.cc ShaderProgram.cc BatchContext.cc Shader.cc

CC = clang++

COMPILER_FLAGS = ""

LINKER_FLAGS = -lSDL2 -lGL -lGLEW -lSDL2_image -lSOIL

OBJ_NAME = main

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
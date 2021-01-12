#SRC specifies which files to compile as part of the project
SRC = $(wildcard *.c)

#CC specifies which compiler we'll be using
CC = gcc

#INCLUDE specifies include directories
# NOTE we include the Nuklear demo dir here to pickup the nuklear to opengl3
# implementation shims
INCLUDE = -I "include/"

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wall turns on lots of warnings
COMPILER_FLAGS = -Wall -Wpedantic -ansi

#LINKER_FLAGS specializes the libraries we're linking against
LIBS = -lglfw -lGL -lm -lGLU -lGLEW

#OBJ_NAME specifies the name of our executable
OBJ_NAME = bin/main

#This is the target that compiles our executable
04: $(SRC)
	$(CC) $(SRC) $(INCLUDE) $(COMPILER_FLAGS) $(LIBS) -o bin/04
all: $(SRC)
	$(CC) $(SRC) $(INCLUDE) $(COMPILER_FLAGS) $(LIBS) -o $(OBJ_NAME)

debug: $(SRC)
	$(CC) $(SRC) $(INCLUDE) $(COMPILER_FLAGS) $(LIBS) -ggdb -o $(OBJ_NAME)

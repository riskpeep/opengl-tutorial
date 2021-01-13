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
all: bin/tut-01

bin:
	mkdir bin

bin/tut-01: bin $(wildcard 01*.c)
	$(CC) tut-01*.c $(INCLUDE) $(COMPILER_FLAGS) $(LIBS) -ggdb -o bin/tut-01

debug: $(SRC)
	$(CC) $(SRC) $(INCLUDE) $(COMPILER_FLAGS) $(LIBS) -ggdb -o $(OBJ_NAME)

clean:
	rm -rf ./bin

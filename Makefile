#SRC specifies which files to compile as part of the project
SRC = $(wildcard *.c)
SHADERS = SimpleVertexShader.vertexshader SimpleFragmentShader.fragmentshader
SHADER_SOURCES = loadShader.c

BINDIR = bin

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
all: $(BINDIR)/tut-01 $(BINDIR)/tut-02

$(BINDIR):
	mkdir $(BINDIR)

$(BINDIR)/tut-01: $(wildcard tut-01*.c) $(SHADERS) $(SHADER_SOURCES) | $(BINDIR)
	$(CC) tut-01*.c $(SHADER_SOURCES) $(INCLUDE) $(COMPILER_FLAGS) $(LIBS) -ggdb -o $@

$(BINDIR)/tut-02: $(wildcard tut-02*.c) $(SHADERS) $(SHADER_SOURCES) | $(BINDIR)
	$(CC) tut-02*.c $(SHADER_SOURCES) $(INCLUDE) $(COMPILER_FLAGS) $(LIBS) -ggdb -o $@

debug: $(SRC)
	$(CC) $(SRC) $(INCLUDE) $(COMPILER_FLAGS) $(LIBS) -ggdb -o $(OBJ_NAME)

clean:
	rm -rf ./$(BINDIR)

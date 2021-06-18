CC=g++

INCLUDE = -I include/
FLAGS=$(shell pkg-config --cflags sdl2) $(INCLUDE) 
LIB_FLAGS=$(shell pkg-config --libs sdl2)

BUILDDIR = build
SRC = $(shell find src/ -type f -name *.cpp)
OBJ = $(patsubst src/%,build/%,$(SRC:.cpp=.o))
TARGET = bin/gol

all: directories $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $(TARGET) $(LIB_FLAGS)

$(BUILDDIR)/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -o $@ $<

directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p bin

clean:
	rm -rf bin/ $(BUILDDIR)

run: all
	./$(TARGET)
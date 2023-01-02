CC=g++
CFLAGS= -Wall -Isrc/ -Wextra -DDEBUG -g -o0

SRCDIR=src

SOURCES=$(shell find ./$(SRCDIR) -name "*.cpp")
EXECUTABLE=main

.PHONY: all
all: build 

build: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

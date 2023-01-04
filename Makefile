CC=g++
CFLAGS= -Wall -Isrc/ -Wextra -DDEBUG -g -o0

SRCDIR=src

SOURCES_MAIN=$(shell find ./$(SRCDIR) -name "*.cpp"  -not -name "test.cpp")
SOURCES_TEST=$(shell find ./$(SRCDIR) -name "*.cpp"  -not -name "main.cpp")
EXECUTABLE=main
TEST=test

.PHONY: all
all: build 

build: $(SOURCES_MAIN) $(EXECUTABLE)
$(EXECUTABLE): $(SOURCES_MAIN)
	$(CC) $(CFLAGS) $(SOURCES_MAIN) -o $@
	
build_test: $(SOURCES_TEST) $(TEST)
$(TEST): $(SOURCES_TEST)
	$(CC) $(CFLAGS) $(SOURCES_TEST) -o $@

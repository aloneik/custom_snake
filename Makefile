CC=g++
CFLAGS=-std=c++17 -g
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics
SOURCES=src/main.cpp src/food.cpp src/snake.cpp
TESTS_SOURCES=tests/tests.cpp src/food.cpp src/snake.cpp
INLCUDES=src/include 
BOOST_INLCUDES=/usr/local/include/boost
EXECUTABLE=snake.out
TESTS_EXECUTABLE=tests.out

all: 
	$(CC) $(CFLAGS) $(SOURCES) -I$(INLCUDES) -I$(BOOST_INLCUDES) $(LDFLAGS) -o $(EXECUTABLE)

test:
	$(CC) $(CFLAGS) $(TESTS_SOURCES) -I$(INLCUDES) -I$(BOOST_INLCUDES) $(LDFLAGS) -o $(TESTS_EXECUTABLE)
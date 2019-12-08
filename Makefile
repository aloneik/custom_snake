CC=g++
CFLAGS=-std=c++17 -g
LDFLAGS=-Lexternal_lib/SFML-2.5.1/lib -lsfml-system -lsfml-window -lsfml-graphics
SOURCES=src/main.cpp src/food.cpp src/snake.cpp
TESTS_SOURCES=tests/tests.cpp src/food.cpp src/snake.cpp
INLCUDES=src/include
SFML_INCLUDES=external_lib/SFML-2.5.1/include
BOOST_INLCUDES=/usr/local/include/boost
EXECUTABLE=snake.out
TESTS_EXECUTABLE=tests.out

all: 
	$(CC) $(CFLAGS) $(SOURCES) -I$(INLCUDES) -I$(SFML_INCLUDES) -I$(BOOST_INLCUDES) $(LDFLAGS) -o $(EXECUTABLE)

test:
	$(CC) $(CFLAGS) $(TESTS_SOURCES) -I$(INLCUDES) -I$(SFML_INCLUDES) -I$(BOOST_INLCUDES) $(LDFLAGS) -o $(TESTS_EXECUTABLE)
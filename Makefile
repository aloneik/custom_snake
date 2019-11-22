all:
	g++ -std=c++17 src/main.cpp src/snake.cpp -o snake.out -Isrc/include -lsfml-system -lsfml-window -lsfml-graphics
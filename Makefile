FLAGS = -std=c++17 -Wall -Wextra -pedantic-errors

build: src/$(NAME).cpp
	mkdir -p build
	g++ $(FLAGS) src/$(NAME).cpp -o build/$(NAME)

run: build/$(NAME)
	./build/$(NAME)


# make run *: build/
#	./build/*

clean-all:
	rm -rf build
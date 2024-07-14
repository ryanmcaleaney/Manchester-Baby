all:
	gcc baby.c binary.c -o baby -lm -Wpedantic -Wall
	./baby
debug:
	gcc baby.c binary.c -o baby -lm -g
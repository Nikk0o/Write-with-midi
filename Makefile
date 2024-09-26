all:
	gcc keymap.c main.c -std=c99 -Wall -o tecladopiano

run:
	sudo ./tecladopiano
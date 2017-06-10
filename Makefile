OBJ = main.o
CFLAGS = $(pkg-config --cflags gtk+-3.0)
LDFLAGS = $(pkg-config --libs gtk+-3.0)

project: $(OBJ)
	gcc -o project $(OBJ) -I$(CFLAGS)

main.o: main.c
	gcc -o 

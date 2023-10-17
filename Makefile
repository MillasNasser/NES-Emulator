# Folders
SRC_FOLDER = src/
OBJ_FOLDER = obj/
LIB_FOLDER = lib/

# Variaveis do projeto
CC = gcc
FLAGS = -pedantic-errors -w -Wextra -Wall -g
SRC = $(wildcard ./**/*.c)
OBJ = $(SRC:.c=.o)
OBJ_PATH = ${subst $(SRC_FOLDER),$(OBJ_FOLDER),$(OBJ)}
EXEC=main

all: main

main: $(OBJ)
	@$(CC) $(FLAGS) -I$(LIB_FOLDER) -o $(EXEC) main.c $(OBJ_PATH)

%.o: %.c
	@$(CC) $(FLAGS) -I$(LIB_FOLDER) -o $(OBJ_FOLDER)$(@F) -c $<

clean:
	@rm -f ./obj/*

clear: clean
	@rm -f main

build: main clean

run: build
	@./$(EXEC)

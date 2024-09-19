
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

EXEC = a4

# Source files and object files
SRC = main.c ghost.c building.c room.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)


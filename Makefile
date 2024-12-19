CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

LIB_NAME = libbmp.a

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

EXAMPLES = $(wildcard examples/*.c)

all: $(LIB_NAME) examples

$(LIB_NAME): $(OBJ)
	@ar rcs $@ $^

examples: $(LIB_NAME)
	@$(CC) $(CFLAGS) -o example examples/example.c -L. -lbmp

clean:
	@rm -f $(OBJ) $(LIB_NAME) example
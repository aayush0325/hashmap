# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g

# Project files
SRC = main.c hashmap.c
OBJ = $(SRC:.c=.o)
TARGET = hashmap_program
DEPS = hashmap.h

# Default target
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compilation rule
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
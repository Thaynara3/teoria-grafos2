# Makefile modelo ajustado para Teoria dos Grafos

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm
TARGET = main
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ) main.exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
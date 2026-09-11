CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = main
OBJS = main.o grafo_matriz.o grafo_lista.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
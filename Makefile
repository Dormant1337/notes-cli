CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = note
PREFIX = /usr/local/bin

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

install: $(TARGET)
	mkdir -p $(PREFIX)
	cp $(TARGET) $(PREFIX)/$(TARGET)

uninstall:
	rm -f $(PREFIX)/$(TARGET)
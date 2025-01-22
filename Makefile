# Makefile for color

CC = g++
CFLAGS = -Wall -Wextra -Ofast -flto -std=c++17
LDFLAGS =

TARGET = color
SRC = color.cpp
OBJ = $(SRC:.cpp=.o)
INSTALL_DIR = /usr/bin/

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

install: $(TARGET)
	@echo "Installing $(TARGET) to $(INSTALL_DIR)..."
	sudo cp $(TARGET) $(INSTALL_DIR)
	sudo chmod +x $(INSTALL_DIR)/$(TARGET)
	@echo "$(TARGET) installed successfully."

clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(TARGET)

reinstall: clean install

help:
	@echo "Makefile for color utility"
	@echo "Usage:"
	@echo "  make           - Build the binary"
	@echo "  make install   - Install the binary to /usr/bin"
	@echo "  make clean     - Clean object files and binary"
	@echo "  make reinstall - Clean and reinstall the binary"
	@echo "  make help      - Show this help message"

.PHONY: all clean install reinstall help


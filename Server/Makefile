# Makefile

CC = g++
CFLAGS = -Wall -std=c++17
BUILDDIR = ./build
TARGET = server.exe
LIBDIR = ./lib

${TARGET}: src/main.cpp src/server.cpp src/fileManager.cpp src/engine.cpp src/object/connexionDetails.cpp src/wrapper.cpp src/encryptionManager.cpp src/client.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $^  -I./../header -lssl -lcrypto -ldl -o $(BUILDDIR)/$@

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Makefile

CC = g++
CFLAGS = -Wall -std=c++17
BUILDDIR = ./build
TARGET = SecTrans
LIBDIR = ./lib

${TARGET}: src/main.cpp src/client.cpp src/fileManager.cpp src/wrapper.cpp src/encryptionManager.cpp src/server.cpp src/engine.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $^  -I./../header -lssl -lcrypto -ldl -o $(BUILDDIR)/$@

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

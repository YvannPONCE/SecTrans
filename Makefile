# Makefile

CC = g++
CFLAGS = -Wall -std=c++17
BUILDDIR = ./build
TARGET = secTrans.exe
LIBDIR = ./lib

${TARGET}: src/main.cpp src/server.cpp src/client.cpp src/fileManager.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $^  -I./../header -ldl -o $(BUILDDIR)/$@

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

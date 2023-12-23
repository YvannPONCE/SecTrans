# Makefile

CC = g++
CFLAGS = -Wall -std=c++11
SRCS = main.cpp
BUILDDIR = ./build
OBJS = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRCS))
TARGET = secTrans
LIBDIR = ./lib
LIBNAME = server

$(TARGET): $(OBJS) $(LIBDIR)/lib$(LIBNAME).so
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBDIR) -l$(LIBNAME) -Wl,-rpath=$(LIBDIR)

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

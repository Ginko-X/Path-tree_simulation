#! /usr/bin/make -rf


VERSION = 0.1

# prefix=/usr/local
# exec_prefix=$(prefix)
# bindir=$(exec_prefix)/bin
# libdir=$(exec_prefix)/lib
# syslibdir=$(libdir)
# sysconfdir=/etc
# includedir=$(prefix)/include
# mandir=$(prefix)/man


CC = gcc
CFLAGS = -Wall #-std=c99 -O0 -g -Wall
#CDEFS = -D_FILE_OFFSET_BITS=64
LD = $(CC)
LDFLAGS = $(CFLAGS)

SOURCES_C = simulation.c path_tree.c #FST.c 
HELPERS =
OBJECTS = simulation.o path_tree.o #FST.o 
EXECUTABLE = simulation

default: compile

.c.o: $(SOURCES_C) $(HELPERS)
	$(CC) $(CFLAGS) -c $<

compile: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

clean:
	-rm -f $(EXECUTABLE) $(OBJECTS)

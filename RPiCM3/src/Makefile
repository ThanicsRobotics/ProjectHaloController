CC=g++-8.1.0
CFLAGS=-Wall -Wextra -Wno-ignored-qualifiers -pthread -std=c++17 -ggdb3 -I/usr/local/include
LIBS=-L/usr/local/lib `pkg-config --cflags --libs gstreamer-1.0` -lwiringPi -lrt -lpigpio -lusb -l:libboost_system.a
SOURCES=$(wildcard *.cpp)
PROJPATH=..
DIR1=-I$(PROJPATH)/inc/
OBJ= $(SOURCES:.cpp=.o)

all: $(OBJ)

.cpp.o:
	$(CC) -c $(CFLAGS) $< $(DIR1) $(LIBS) -o $@

clean:
	rm -f *.o
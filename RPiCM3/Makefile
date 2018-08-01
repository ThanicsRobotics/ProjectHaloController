CC=g++-8.1.0
CFLAGS=-Wall -Wextra -pthread -std=c++17 -ggdb3 -I/usr/local/include
LIBS=-L/usr/local/lib `pkg-config --cflags --libs gstreamer-1.0` -lwiringPi -lrt -lpigpio -lusb -l:libboost_system.a
PROJPATH=.
DIR1=$(PROJPATH)/src/
OBJ=$(patsubst %.cpp,%.o,$(wildcard $(DIR1)*.cpp))
EXEC=halo-controller

all:
	+$(MAKE) -C src
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(EXEC)

clean:
	+$(MAKE) clean -C src
	rm -f $(EXEC)

install:
	cp $(EXEC) /usr/bin/

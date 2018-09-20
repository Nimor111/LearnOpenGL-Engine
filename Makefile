CPPSRC = $(wildcard src/*.cpp) 
CSRC = $(wildcard src/*.c)
OBJECTS = $(CSRC:.c=.o) $(CPPSRC:.cpp=.o)
CC = g++
CFLAGS = -Wall -I.
LDFLAGS = -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -std=c++11 -ldl

all: main clean

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJECTS)

# Macros:
CPP= g++
CFLAGS= -O3 -fopenmp

all: samplecode

samplecode: graph.o BurningDecoder.o samplecode.o 
	$(CPP) $(CFLAGS) graph.o BurningDecoder.o samplecode.o -o samplecode

graph.o: graph.cpp
	$(CPP) $(CFLAGS) -c graph.cpp

BurningDecoder.o: BurningDecoder.cpp
	$(CPP) $(CFLAGS) -c BurningDecoder.cpp

samplecode.o: samplecode.cpp
	$(CPP) $(CFLAGS) -c samplecode.cpp

# Remove:
.PHONE: clean
clean:
	rm -f sampledecode *.o

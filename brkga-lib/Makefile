# Macros:
CPP= g++
CFLAGS= -O3 -fopenmp

all: samplecode

samplecode: BurningDecoder.o samplecode.o
	$(CPP) $(CFLAGS) BurningDecoder.o samplecode.o -o samplecode
        
BurningDecoder.o: BurningDecoder.cpp
	$(CPP) $(CFLAGS) -c BurningDecoder.cpp

samplecode.o: samplecode.cpp
	$(CPP) $(CFLAGS) -c samplecode.cpp

# Remove:
.PHONE: clean
clean:
	rm -f sampledecode *.o

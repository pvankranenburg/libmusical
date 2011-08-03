#FLAGS = -O3 -pg
FLAGS = -O3

all:
	g++ -c ${FLAGS} -o MeterCollection.o MeterCollection.cpp
	g++ -c ${FLAGS} -o MetroWeights_Mazzola.o MetroWeights_Mazzola.cpp
	g++ -c ${FLAGS} -o Metrum.o Metrum.cpp
	g++ -c ${FLAGS} -o OnsetGroup_Memory.o OnsetGroup_Memory.cpp
	ar rvs libIMACPP.a *.o

clean:
	rm *.o libIMACPP.a

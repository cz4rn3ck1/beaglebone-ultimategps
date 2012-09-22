gpsTest : gps.o gpsTest.cc
	g++ -g -Wall -o gpsTest gps.o gpsTest.cc
gps.o : gps.h gps.cc
	g++ -c -g -Wall -o gps.o gps.cc
clean : 
	rm gps.o gpsTest.o

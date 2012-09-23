gpsTest : gps.o nmea.o gpsTest.cc
	g++ -g -Wall -o gpsTest gps.o nmea.o gpsTest.cc

gps.o : gps.h gps.cc
	g++ -c -g -Wall -o gps.o gps.cc
nmea.o : gps.h nmea.cc
	g++ -c -g -Wall -o nmea.o nmea.cc

clean : 
	rm gps.o gpsTest.o

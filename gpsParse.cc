/*
 *
 */
#include <iostream>
#include <string>
#include "gps.h"

using namespace std;

int main(int argc, char** argv) {
  GPS gps;
  if (gps.Init()) {
    
    fstream gpsStr;
    gpsStr.open("/dev/ttyO2", ios::in );
    if (gpsStr.good()) {
      string line;
      for (int i = 0; i < 50; i++) {
	getline(gpsStr, line);
	gps.StoreNMEA(line);
      }
      gpsStr.close();
    }
  }
  return 0;
}

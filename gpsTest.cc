/*
 *
 */
#include <iostream>
#include <string>
#include "gps.h"

using namespace std;

int main(int argc, char** argv) {
  cout << "GPS Test:" << endl;
  
  GPS gps;
  
  //gps.StoreNMEA("$GPGGA,064951.000,2307.1256,N,12016.4438,E,1,8,0.95,39.9,M,17.8,M,,*65");
  //gps.StoreNMEA("$GPGSA,A,3,29,21,26,15,18,09,06,10,,,,,2.32,0.95,2.11*00");
  //gps.StoreNMEA("$GPGSV,3,1,09,29,36,029,42,21,46,314,43,26,44,020,43,15,21,321,39*7D");
  //gps.StoreNMEA("$GPGSV,3,2,09,18,26,314,40,09,57,170,44,06,20,229,37,10,26,084,37*77");
  //gps.StoreNMEA("$GPGSV,3,3,09,07,,,26*73");
  gps.StoreNMEA("$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C");
  //gps.StoreNMEA("$GPVTG,165.48,T,,M,0.03,N,0.06,K,A*37");
  
  return 0;
}

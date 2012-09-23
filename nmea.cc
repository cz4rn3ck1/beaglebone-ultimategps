/*
 * copyright: CC-By 3.0
 * author: cz4rn3ck1
 *
 * the purpose of this class is to read and extract data from nmea strings
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "gps.h"

using namespace std;


void GPS::StoreNMEA(string nmea) {
  if (!ValidateNMEA(nmea)) {
    cout << "nmea string checksum failed: " << nmea << endl;
    return;
  }
    
  vector<string> nmea_vector = SplitNMEA(nmea);

  if (nmea_vector[0].compare("$GPRMC") == 0)
    StoreRMC(nmea_vector);
}

vector<string> GPS::SplitNMEA(string nmea) {
  vector<string> split_nmea;

  while (nmea.find(",") != string::npos) {
    split_nmea.push_back(nmea.substr(0, nmea.find(",")));
    nmea.erase(0, nmea.find(",")+1);
  }
  split_nmea.push_back(nmea.substr(0, nmea.find("*")));

  return split_nmea;
}

bool GPS::ValidateNMEA(string nmea) {
  unsigned int xfer_checksum;
  stringstream ss;
  ss << std::hex << nmea.substr(nmea.find("*",1)+1, 2);
  ss >> xfer_checksum;

  unsigned int calc_checksum = 0;
  for (unsigned int c = 1; c < nmea.length(); c++) {
    if (nmea[c] == '*') break;
    calc_checksum ^= nmea[c] & 0xff;
  }
  
  return xfer_checksum == calc_checksum;
}

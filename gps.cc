/*
 * copyright: CC-By 3.0
 * author: cz4rn3cki
 *
 * this is the source file for the gps object described in gps.h
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//#include <cstdint>
#include <cstdlib>

#include "gps.h"

using namespace std;

GPS::GPS(void) {
  status_ = "";
  mode_ = "";
  date_ = "";
  time_ = "";
  latitude_ = "";
  longitude_ = "";
  course_ = "";
  velocity_ = "";
  magnetic_variation_ = "";
}

bool GPS::Init(void) {
  // setup tty for device file
  int setup_status = system("stty --file=/dev/ttyO2 9600 -ixon -ixoff nl cs8");
  // return true if successful
  return setup_status == 0;
}

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

void GPS::StoreRMC(vector<string> sentence) {
  time_ = sentence[1];
  time_ = time_.substr(0,2) + ":" + time_.substr(2,2) +
    ":" + time_.substr(4,2);
  
  status_ = sentence[2];
  latitude_ = sentence[3] + sentence[4];
  longitude_ = sentence[5] + sentence[6];
  velocity_ = sentence[7];
  course_ = sentence[8];

  date_ = sentence[9];
  date_ = date_.substr(2,2) + "/" + date_.substr(0,2) + 
    "/" + date_.substr(4,2);
  
  magnetic_variation_ = sentence[10] + "(" + sentence[11] + ")";
  mode_ = sentence[12];

  PrintRMC();
}

void GPS::PrintRMC(void) {
  cout << "recommended minimum navigation information" << ":" << endl;
  if (!status_.compare("V") || !status_.compare("A")) {
    cout << "  status: " << status_;
    cout << "  mode: " << mode_ << endl;
    cout << "  " << date_ << " " << time_ << endl;
    if (!status_.compare("A")) {
      cout << "  lat,lon: " << latitude_ << "," << longitude_ << endl;
      cout << "  velocity: " << velocity_ << "knots";
      cout << "  course: " << course_ << "deg" << endl;
      cout << "  magnetic variation: " << magnetic_variation_ << "deg" << endl;
    }
  }
}

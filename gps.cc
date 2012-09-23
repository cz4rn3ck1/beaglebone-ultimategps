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
  latitude_ = 0.0;
  longitude_ = 0.0;
  course_ = 0.0;
  velocity_ = 0.0;
  magnetic_variation_ = "";
}

bool GPS::Init(void) {
  // setup tty for device file
  int setup_status = system("stty --file=/dev/ttyO2 9600 -ixon -ixoff nl cs8");
  // return true if successful
  return setup_status == 0;
}

void GPS::StoreRMC(vector<string> sentence) {
  time_ = sentence[1];
  time_ = time_.substr(0,2) + ":" + time_.substr(2,2) +
    ":" + time_.substr(4,2);
  
  status_ = sentence[2];
  latitude_ = strtod(sentence[3].c_str(), NULL);
  if (sentence[4].compare("S") == 0) latitude_ *= -1;
  longitude_ = strtod(sentence[5].c_str(), NULL);
  if (sentence[6].compare("W") == 0) longitude_ *= -1;
  
  velocity_ = strtod(sentence[7].c_str(), NULL);
  course_ = strtod(sentence[8].c_str(), NULL);

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
      cout << "  lat,lon: " << latitude_ << ", " << longitude_ << endl;
      cout << "  velocity: " << velocity_ << "knots";
      cout << "  course: " << course_ << "deg" << endl;
      cout << "  magnetic variation: " << magnetic_variation_ << "deg" << endl;
    }
  }
}

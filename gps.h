/*
 * copyright: CC-By 3.0
 * author: cz4rn3ck1
 *
 * The purpose of the GPS class is to perform the following
 *   - read the data stream from the device's tty file
 *   - parse and interpret the data
 *   - store the relevant data
 *   - output the interpretted data in a form that is easy to access and read
 */
#ifndef LIBRARIES_GPS_GPS_
#define LIBRARIES_GPS_GPS_

#include <string>
#include <vector>
//#include <cstdint>

using namespace std;

/* class
 * @name GPS
 * @desc encompassing class for gps operation
 */
class GPS {

public:
  // constructor
  GPS(void);
  bool Init(void); // returns true if object is init'd properly

  // data storage functions
  void StoreNMEA(string);

  // accessor functions
  //string status(void);
  //string mode(void);
  //string date(void);
  //string time(void);
  
private:
  // read the data stream from the device's tty file
  // fstream* getDevStream(string);
  
  // parse, validate, and interpret the data
  vector<string> SplitNMEA(string);
  bool ValidateNMEA(string);
  
  // store the relevant data
  void StoreRMC(vector<string>);

  // output the interpretted data in a form that is easy to access and read
  void PrintRMC(void);
  
  // mutator functions
  //void set_status(string);
  //void set_mode(string);
  //void set_date(string);
  //void set_time(string);
  
  // data members
  string status_; // A=valid position, V=no valid position, blank=no valid data
  string mode_; // A=autonomous,D=differential,E=estimated
  string date_; // ddmmyy
  string time_; // hhmmss.sss
  double latitude_; // ddmm.mmmmN
  double longitude_; // dddmm.mmmmW
  double course_; // course over ground in degrees
  double velocity_; // velocity over ground in knots
  string magnetic_variation_; // magnetic variation measured in degrees
};

#endif // LIBRARIES_GPS_GPS_

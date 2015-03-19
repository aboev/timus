#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>

using namespace std;

const int STATE_DEFAULT = 0;
const int STATE_SHIP_LAT = 1;
const int STATE_SHIP_LONG = 2;
const int STATE_STATE2 = 3;
const int STATE_ICEB_LAT = 4;
const int STATE_ICEB_LONG = 5;
const int STATE_COMPLETE = 6;

const double pi = acos(-1.0);

double convert(string input) {
  int deg, min, sec;
  double res;
  int pos1 = input.find("^");
  deg = atoi( input.substr(0, pos1).c_str() );
  int pos2 = input.find("'");
  min = atoi( input.substr(pos1 + 1, pos2 - pos1).c_str() );
  int pos3 = input.find("\"");
  sec = atoi( input.substr(pos2 + 1, pos3 - pos2).c_str() );
  res = (deg + min / 60.0 + sec / 3600.0) * pi / 180.0;
  if ((input.find("S") != string::npos) || (input.find("W") != string::npos))
    res = -res;
  return res;
}

int main (int argc, char **argv) {
  int state = STATE_DEFAULT; 
  char buf[100];
  string input;
  double ship_lat, ship_long, iceb_lat, iceb_long;
  while (state != STATE_COMPLETE) {
    getline (cin, input);
    int deg, min, sec;
    if (state == STATE_SHIP_LAT) {
      ship_lat = convert(input);
      state = STATE_SHIP_LONG;
    } else if (state == STATE_SHIP_LONG) {
      ship_long = convert(input.substr(4, input.length() - 4));
      state = STATE_STATE2;
    } else if (state == STATE_STATE2) {
      state = STATE_ICEB_LAT;
    } else if (state == STATE_ICEB_LAT) {
      iceb_lat = convert(input);
      state = STATE_ICEB_LONG;
    } else if (state == STATE_ICEB_LONG) {
      iceb_long = convert(input.substr(4, input.length() - 4));
      state = STATE_COMPLETE;
    }
    if (input.find("Current") != string::npos) state = STATE_SHIP_LAT;
    else if (input.find("An") != string::npos) state = STATE_ICEB_LAT;
  }
  double delta = ship_long - iceb_long;
  double radius = 3437.5;
  double dist = acos (sin(ship_lat) * sin(iceb_lat) + cos(ship_lat) * cos(iceb_lat) * cos(delta)) * radius;
  printf("The distance to the iceberg: %.2f miles.\n", dist);
  if (100.00 - dist > 0.005) printf("DANGER!\n");
  return 0;
}

#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

#define PI 3.14159265

float get_dist(float x0, float y0, float x1, float y1) {
  return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)); 
}

float get_len(float x0, float y0, float x1, float y1, float x2, float y2, float R) {
  float res = 0;
  float a = get_dist(x0, y0, x1, y1);
  float b = get_dist(x1, y1, x2, y2);
  float c = get_dist(x0, y0, x2, y2);
  float angle_cos = (a * a + b * b - c * c) / (2 * a * b);
  res = a + (PI - acos(angle_cos)) * R;
  return res;
}

int main (int argc, char **argv) {
  int N;
  float R, len = 0, x00, y00, x01, y01, x0, y0, x1, y1, x2, y2;
  scanf("%d %f", &N, &R);
  scanf("%f %f", &x0, &y0);
  scanf("%f %f", &x1, &y1);
  x00 = x0, y00 = y0;
  x01 = x1, y01 = y1;
  if (N == 1) {
    len = 2 * PI * R;
  } else if (N == 2) {
    len = 2 * get_len(x0, y0, x1, y1, x0, y0, R);
  } else {
    for (int i = 2; i < N; i++) {
      scanf("%f %f", &x2, &y2);
      len = len + get_len(x0, y0, x1, y1, x2, y2, R);

      x0 = x1; y0 = y1;
      x1 = x2; y1 = y2;
    }
    len = len + get_len(x0, y0, x1, y1, x00, y00, R) + get_len(x1, y1, x00, y00, x01, y01, R);
  }
  printf("%.2f\n", len);
  
  return 0;
}

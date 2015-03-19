#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <math.h>

using namespace std;

map<unsigned short, double> cache;

void put_cache(int sum, int cols, double val) {
  unsigned short id = sum * 100 + cols;
  cache.insert(pair<unsigned short, double>(id, val));
}

double get_cache(int sum, int cols) {
  unsigned short id = sum * 100 + cols;
  if (cache.find(id) != cache.end()) return cache.find(id)->second;
  else return -1;
}

double get_count_dp(int sum, int cols) {
  double res = 0;
  if ((res = get_cache(sum, cols)) != -1) return res;
  int t = cols + cols * cols;
  if (t == 2 * sum) res = 1;
  else if (t > 2 * sum) res = 0;
  else {
    double t1 = ((cols > 2) && (sum - cols > 0)) ? get_count_dp(sum - cols, cols - 1) : 1;
    double t2 = ((cols > 1) && (sum - cols > 0)) ? get_count_dp(sum - cols, cols) : 1;
    res = t1 + t2;
  }
  put_cache(sum, cols, res);
  return res;
}

int get_max_cols(int sum) {
  int i = 0;
  while ((i * i + i) < 2 * sum) i++;
  return i;
}

double get_count (int sum) {
  int max_cols = get_max_cols(sum);
  double res = 0;
  for (int i = 2; i <= max_cols; i++) {
    res += get_count_dp(sum, i);
  }
  return res;
}

int main (int argc, char **argv) {
  int N;
  scanf("%d", &N);
  printf("%.0f\n", get_count(N));
  return 0;
}

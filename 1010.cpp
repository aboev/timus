#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int main(int argc, char** argv) {
  int n;
  vector<long long> vals;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int val;
    scanf("%d", &val);
    vals.push_back(val);
  }
  long long max = 0;
  int res = 0;
  for (int i = 1; i < n; i++) {
    //printf("abs(%lli - %lli) = %lli \n", vals[i], vals[i-1], abs(vals[i] - vals[i-1]));
    if (abs(vals[i] - vals[i-1]) > max) {
      max = abs(vals[i] - vals[i-1]);
      res = i-1;
    }
  } 
  printf("%d %d\n", res + 1, res + 2);
}


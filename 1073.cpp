#include <stdio.h>  
#include <vector>
#include <map>
#include <math.h>
#include <iostream>
 
using namespace std;  

const int log_tag = false;
//const int log_tag = true;

int main (int argc, char **argv) {
  int K;
  scanf("%d", &K);
  int cost[K + 1];
  cost[0] = 0; cost[1] = 1;
  for (int i = 2; i <= K; i++) {
    if (round(sqrt(i)) * round(sqrt(i)) == i) {
      cost[i] = 1;
    } else {
      int min = i;
      for (int j = 1; j * j < i; j++)
        if ((cost[j * j] + cost[i - j * j]) < min)
          min = cost[j * j] + cost[i - j * j];
      cost[i] = min;
    }
  }
  printf("%d\n", cost[K]);
  return 0;
} 

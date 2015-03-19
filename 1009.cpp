#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int main(int argc, char** argv) {
  int N, K;
  scanf("%d %d", &N, &K);
  int f1 = K - 1;
  int f2 = K * K - K;
  int res = f1;
  int i = 3;
  while (i <= N) {
    //printf("Iteration %i, f1 = %d, f2 = %d \n", i, f1, f2);
    res = f2;
    f2 = (K - 1) * (f1 + f2);
    f1 = res;
    i++;
  }
  if (N == 1) printf("%d\n", f1);
  else printf("%d\n", f2);
}


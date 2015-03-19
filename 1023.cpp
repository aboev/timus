#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

int main (int argc, char **argv) {
  int K;
  scanf("%d", &K);
  int N = 2;
  int L = 0;
  while (true) {
    if (K % (N + 1) == 0) {L = N; break;}
    else if ((N + 1) * (N + 1) < K) N++;
    else if ((K % 2 == 0) && (K > 4)) {L = K / 2 - 1; break;}
    else {L = K - 1; break;}
  }
  printf("%d\n", L);
  return 0;
}

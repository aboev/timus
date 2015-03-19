#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

int main (int argc, char **argv) {
  int K, num = 0;
  scanf("%d", &K);
  vector<int> P;
  for (int i = 0; i < K; i++) {
    int tmp; scanf("%d", &tmp);
    P.push_back(tmp);
  }
  sort(P.begin(), P.end());
  for (int i = 0; i * 2 <= K; i++) num += (P[i] + 1) / 2;
  printf("%d\n", num);

  return 0;
}

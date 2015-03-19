#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

int main (int argc, char **argv) {
  int N, K;
  scanf("%d", &N);
  vector<int> data;
  for (int i = 0; i < N; i++) {
    int tmp; scanf("%d", &tmp);
    data.push_back(tmp);
  }
  char sep[4];
  scanf("%s", sep);
  scanf("%d", &K);
  sort(data.begin(), data.end());
  for (int i = 0; i < K; i++) {
    int pos;
    scanf("%d", &pos);
    printf("%d\n", data[pos - 1]);
  }
  return 0;
}

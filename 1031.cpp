#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits.h>
#include <string>

using namespace std;

int L[3] = {0}, C[3] = {0}, from, to, n;
int prev1[10001], prev2[10001], prev3[10001];
vector<int> dist, cost;

const bool log_tag = false;
//const bool log_tag = true;

void init() {
  int p1 = from, p2 = from, p3 = from;
  for (int i = from; i <= to; i++) {
    while ((dist[i] - dist[p1]) > L[0]) p1++;
    while ((dist[i] - dist[p2]) > L[1]) p2++;
    while ((dist[i] - dist[p3]) > L[2]) p3++;
    prev1[i] = p1;
    prev2[i] = p2;
    prev3[i] = p3;
    if (log_tag) printf("prev1[%d] = %d, prev2[%d] = %d, prev3[%d] = %d \n", i, prev1[i], i, prev2[i], i, prev3[i]);
  }
}

void get_shortest(int from, int to) {
  for (int i = from + 1; i <= to; i++) {
    int cost1 = prev1[i] == i ? INT_MAX : cost[prev1[i]] + C[0];
    int cost2 = prev2[i] == i ? INT_MAX : cost[prev2[i]] + C[1];
    int cost3 = prev3[i] == i ? INT_MAX : cost[prev3[i]] + C[2];
    cost[i] = min(min(cost1, cost2), cost3);
    if (log_tag) printf("cost1 = %d, cost2 = %d, cost3 = %d, cost[%d] = %d \n", cost1, cost2, cost3, i, cost[i]);
  }
}

int main (int argc, char **argv) {
  scanf("%d %d %d %d %d %d", &L[0], &L[1], &L[2], &C[0], &C[1], &C[2]);
  scanf("%d", &n);
  scanf("%d %d", &from, &to);
  from = from - 1; to = to - 1;
  if (to < from) {
    int tmp = to;
    to = from;
    from = tmp;
  }
  dist.push_back(0);
  cost.push_back(0);
  int prev_dist = 0, tmp = 0;
  for (int i = 0; i < n - 1; i++) {
    scanf("%d", &tmp);
    //dist.push_back(tmp - prev_dist);
    dist.push_back(tmp);
    cost.push_back(0);
    prev_dist = tmp;
  }
  init();
  get_shortest(from, to);
  printf("%d\n", cost[to]);
  return 0;
}

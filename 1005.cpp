#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> vals;

int knapsack(int sum, unsigned char bound) {
  //printf("Running knapsack for sum = %d, bound = %d \n", sum, bound);
  vector<int>::iterator next = upper_bound (vals.begin(), vals.begin() + bound, sum);
  if ((bound == -1) || (next - vals.begin() <= 0)) {
    //printf("backtracking with %d\n", sum);
    return sum;
  }
  return min(knapsack(sum - vals[next - vals.begin() - 1], next - vals.begin() - 1), knapsack(sum, next - vals.begin() - 1));
}

int main(int argc, char * argv[]) {
#ifndef ONLINE_JUDGE
   //log = true;
   //freopen("input.txt", "rt", stdin);
   //freopen("output.txt", "wt", stdout);
#endif
  int i=0, b;
  int sum = 0;
  scanf("%d\n", &i);
  for (int j = 0; j < i; j++) {
    scanf("%d", &b);
    //cin >> b;
    vals.push_back(b);
    sum += b;
  }
  sort (vals.begin(), vals.end());
  printf("%d\n", abs(sum - 2 * (sum / 2 - knapsack(sum / 2, vals.size()))));
  return 0;
}

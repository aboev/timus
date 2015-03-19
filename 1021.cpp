#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

vector<int> list1, list2;

int main (int argc, char **argv) {
  int N1, N2, t;
  scanf("%d", &N1);
  const int val = 10000;
  for (int i = 0; i < N1; i++) {
    scanf("%d", &t);
    list1.push_back(t);
  }
  scanf("%d", &N2);
  for (int i = 0; i < N2; i++) {
    scanf("%d", &t);
    list2.push_back(t);
  }
  sort(list1.begin(), list1.end());
  sort(list2.begin(), list2.end());
  int i = 0, j = list2.size() - 1;
  while (((list1[i] + list2[j]) != val) && (i < list1.size()) && (j >= 0)) {
    if (list1[i] + list2[j] > val) j--;
    if (list1[i] + list2[j] < val) i++;
  }
  if ((i < list1.size()) && (j >= 0) && ((list1[i] + list2[j]) == val)) printf("YES\n");
  else printf("NO\n");
  return 0;
}

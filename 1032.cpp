#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

const bool log_tag = false;
//const bool log_tag = true;

int main (int argc, char **argv) {
  int n, tmp, sum = 0;
  bool ok = false;
  vector<int> nums;
  map<int, int> mod_map;
  scanf("%d", &n);
  mod_map[0] = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &tmp);
    nums.push_back(tmp);
    sum = sum + tmp;
    if (mod_map.find(sum % n) != mod_map.end()) {
      printf("%d\n", i - mod_map[sum % n] + 1);
      for (int j = mod_map[sum % n]; j < i + 1; j++)
        printf("%d\n", nums[j]);
      ok = true;
      break;
    } else mod_map[sum % n] = i + 1;
  }
  if (!ok) printf("0\n");
  return 0;
}

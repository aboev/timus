#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long int pow (unsigned long int num, unsigned long int power) {
  if (power == 0) {
    return 1;
  } else if (power % 2 == 1) {
    return pow(num, power - 1) * num;
  } else {
    return pow(num, power / 2) * pow(num, power / 2);
  }
}

int main (int argc, char **argv) {
  vector<int> factors;
  int N;
  scanf("%d", &N);
  if (N == 1) {printf("1\n"); return 0;}
  else if (N == 0) {printf("10\n"); return 0;}
  int power = 0;
  
  for (int i = 9; i > 1 ; i--)
    if (N % i == 0) {
      power = 0;
      unsigned long int p1 = 0, p2 = 0;
      while (N % i == 0) {
        N /= i;
        power++;
        p1 = pow(i, power);
        p2 = pow(i, power + 1);
        if ((p1 <= 9) && (p2 > 9)) {
          factors.push_back(p1);
          power = 0;
        }
      }
      if (power) factors.push_back(p1);
    }
  if (N > 1) {
    printf("-1\n"); 
    return 0;
  }
  sort(factors.begin(), factors.end());
  for (int i = 0; i < factors.size(); i++) printf("%d", factors[i]);
  printf("\n");
  return 0;
}

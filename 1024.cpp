#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

bool compare(int *v1, int *v2, int len) {
  for (int i = 0; i < len; i++)
    if (v1[i] != v2[i]) return false;
  return true;
}

bool compare_ext(int *v1, int *v2, int len, int *L, int pos) {
  int cnt = 0;
  for (int i = 0; i < len; i++) {
    if ((v1[i] == v2[i]) && (L[i] == 0)) L[i] = pos; 
    if (L[i] != 0) cnt++;
  }
  return cnt == len;
}

int* transform(int *v1, int *v2, int len) {
  int *res = new int[len];
  for (int i = 0; i < len; i++) res[i] = v1[v2[i] - 1];
  return res;
}

int gcd (int a, int b) {
  return b ? gcd (b, a % b) : a;
}

int lcm (int a, int b) {
  return a / gcd (a, b) * b;
}

int main (int argc, char **argv) {
  int N, E;
  scanf("%d", &N);
  int *P, *P_0, *P_cur, *L, pos = 1;
  P = new int[N]; P_0 = new int[N]; L = new int[N];
  for (int i = 0; i < N; i++) {
    int tmp = 0;
    scanf("%d", &P[i]);
    P_0[i] = i + 1;
    L[i] = 0;
  }
  P = transform(P_0, P, N); P_cur = P;
  if (compare(P, P_0, N)) pos = 1;
  else {
    compare_ext(P_cur, P_0, N, L, 1);
    P_cur = transform(P, P_cur, N);
    pos = 2;
    while (!compare_ext(P_cur, P_0, N, L, pos)) {
      int *tmp = transform(P, P_cur, N);
      delete [] P_cur;
      P_cur = tmp;
      pos++;
    }
    pos = lcm(L[0], L[1]);
    for (int i = 2; i < N; i++) pos = lcm(pos, L[i]);
  }
  printf("%d\n", pos);

  return 0;
}

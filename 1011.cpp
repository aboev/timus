#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

void conv(char *a, short int& n) {
  char *tmp = new char[strlen(a)];
  int j = 0;
  for (int i = 0; i <= strlen(a); i++) {
    if (a[i] != '.') {
      tmp[j] = a[i];
      j++;
    }
  }
  n = atoi(tmp);
  char *pos = strstr(a, ".");
  if ((pos != NULL) && (a - pos + strlen(a) == 2)) n = n * 10;
  else if (pos == NULL) n = n * 100;
}

int main(int argc, char** argv) {
  char buf1[10], buf2[10];
  scanf("%s %s", buf1, buf2);
  short int P, Q;
  conv(buf1, P);
  conv(buf2, Q);
  int i = 0;
  while ((Q - P) * i + P * i % 10000 <= 10000) {i++;}
  printf("%d\n", i);
  return 0;
}

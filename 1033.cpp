#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

const bool log_tag = false;
//const bool log_tag = true;

bool **plan;
char **visit;
int s = 0, n;

void traverse(int x, int y) {
  if (!plan[x][y] && (visit[x][y] == 0)) {
    visit[x][y] = visit[x][y] | 1<<4;
    if ((x < n) && !plan[x + 1][y]) traverse(x + 1, y);
    else if ((x < n + 1) && plan[x + 1][y] && ((visit[x + 1][y] & (1 << 3)) == 0)) {
      visit[x + 1][y] = visit[x + 1][y] | (1 << 3);
      s++;
    }
    if ((x > 1) && !plan[x - 1][y]) traverse(x - 1, y);
    else if ((x > 0) && plan[x - 1][y] && ((visit[x - 1][y] & (1 << 2)) == 0)) {
      visit[x - 1][y] = visit[x - 1][y] | (1 << 2);
      s++;
    }
    if ((y < n) && !plan[x][y + 1]) traverse(x, y + 1);
    else if ((y < n + 1) && plan[x][y + 1] && ((visit[x][y + 1] & (1 << 1)) == 0)) {
      visit[x][y + 1] = visit[x][y + 1] | (1 << 1);
      s++;
    }
    if ((y > 1) && !plan[x][y - 1]) traverse(x, y - 1);
    else if ((y > 0) && plan[x][y - 1] && ((visit[x][y - 1] & 1) == 0)) {
      visit[x][y - 1] = visit[x][y - 1] | 1;
      s++;
    }
  }
}

int main (int argc, char **argv) {
  char c;
  scanf("%d", &n);
  //bool map[n + 1][n + 1];
  char line[n + 1];
  plan = new bool*[n + 2];
  visit = new char*[n + 2];
  for (int i = 0; i < n; i++) {
    plan[i] = new bool[n + 2];
    visit[i] = new char[n + 2];
  }
  plan[n + 1] = new bool[n + 2];
  plan[n] = new bool[n + 2];
  visit[n + 1] = new char[n + 2];
  visit[n] = new char[n + 2];
  for (int i = 0; i < n + 2; i++) {
    for (int j = 0; j < n + 2; j++) {
      plan[i][j] = false;
      visit[i][j] = 0;
    }
  }
  for (int i = 0; i < n; i++) {
    scanf("%s", line);
    for (int j = 0; j < n; j++) {
      c = line[j];
      plan[i + 1][j + 1] = c == '#';
      if ((i == 0) && (j > 0)) plan[i][j + 1] = true;
      if ((i == (n - 1)) && (j < (n - 1))) plan[i + 2][j + 1] = true;
      visit[i + 1][j + 1] = 0;
    }
    if (i < n - 1) {
      plan[i + 2][0] = true;
      plan[i + 1][n + 1] = true;
    }
  }

  traverse(1, 1);
  traverse(n, n);

  printf("%d\n", s * 9);

  return 0;
}

#include <stdio.h>
#include <vector>
#include <stdlib.h>

using namespace std;

bool log_tag = false;
//const bool log_tag = true;

int n;
vector<pair<char, char> > queens;

bool issafe(char a, char b) {
  char xa = queens[a].first;
  char ya = queens[a].second;
  char xb = queens[b].first;
  char yb = queens[b].second;
  if (log_tag) printf("%d:%d and %d:%d is %s\n", xa, ya, xb, yb, ((xa == xb) || (ya == yb) || (abs(xa - xb) == abs(ya - yb))) ? "not safe" : " safe");
  return !((xa == xb) || (ya == yb) || (abs(xa - xb) == abs(ya - yb)));
}

void swap(char a, char b) {
  char xa = queens[a].first;
  char ya = queens[a].second;
  //queens[a].first = queens[b].first;
  queens[a].second = queens[b].second;
  //queens[b].first = xa;
  queens[b].second = ya;
  if (log_tag) printf("Swapping %d:%d and %d:%d \n", xa, ya, queens[a].first, queens[a].second);
}

void draw() {
  bool board[n][n];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      board[i][j] = false;
  for (int i = 0; i < n; i++)
    board[queens[i].second][queens[i].first] = true;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      printf("%c ", board[i][j] ? 'o' : '+');
    printf("\n");
  }
}

int main (int argc, char **argv) {
  int x, y, count = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &x, &y);
    queens.push_back(pair<char, char>(x - 1, y - 1));
  }
  
  if (log_tag) draw();

  for (char i = 0; i < n; i++) {
    for (char j = i + 1; j < n; j++) {
      for (char k = j + 1; k < n; k++ ) {
        swap(i, j);
        swap(j, k);
        bool safe = true;
        for (char l = 0; l < n; l++) {
          if ((i != l) && !issafe(i, l)) {safe = false; break;}
          if ((j != l) && !issafe(j, l)) {safe = false; break;}
          if ((k != l) && !issafe(k, l)) {safe = false; break;}
        }
        if (safe) count++;
        swap(i, j);
        swap(j, k);
        safe = true;
        for (char l = 0; l < n; l++) {
          if ((i != l) && !issafe(i, l)) {safe = false; break;}
          if ((j != l) && !issafe(j, l)) {safe = false; break;}
          if ((k != l) && !issafe(k, l)) {safe = false; break;}
        }
        if (safe) count++;
        swap(i, j);
        swap(j, k);
      }
    }
  }
  printf("%d\n", count);
  
  return 0;
}

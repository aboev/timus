#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

vector<vector<short int>* > vals;
vector<short int> levels;

short int get_bucket(short int i) {
  return i / 180;
}

int main (int argc, char **argv) {
  int N, x, y;
  scanf("%d", &N);
  for (short int i = 0; i < 180; i++) {
    vector<short int> *v = new vector<short int>();
    vals.push_back(v);
  }
  levels = vector<short int>(N, 0);
  for (short int i = 0; i < N; i++) {
    scanf("%d %d", &x, &y);
    short int bnum = get_bucket(x);
    short int level = 0;
    for (short int j = 0; j < get_bucket(x); j++) level = level + vals[j]->size();
    for (short int j = 0; j < vals[bnum]->size(); j++) if ((*vals[bnum])[j] <= x) level++;
    levels[level] = levels[level] + 1;
    vals[bnum]->push_back(x);
  }
  for (int i = 0; i < N; i++) printf("%d\n", levels[i]);
  return 0;
}

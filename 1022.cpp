#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

vector<vector<int> > nodes;
vector<bool> marked;

void dfs(int id, vector<int> *seq) {
  marked[id] = true;
  for (int i = 0; i < nodes[id].size(); i++)
    if (!marked[nodes[id][i] - 1]) dfs(nodes[id][i] - 1, seq);
  seq->push_back(id + 1);
}

int main (int argc, char **argv) {
  int N, id = -1;
  scanf("%d", &N);
  marked = vector<bool>(N, false);
  for (int i = 0; i < N; i++) {
    vector<int> tmp;
    scanf("%d", &id);
    while (id != 0) {
      tmp.push_back(id);
      scanf("%d", &id);
    }
    nodes.push_back(tmp);
  }
  vector<int> *seq = new vector<int>;
  for (int i = 0; i < N; i++) if (!marked[i]) dfs(i, seq);
  reverse(seq->begin(), seq->end());
  for (int i = 0; i < seq->size(); i++) printf("%d ", (*seq)[i]);
  return 0;
}

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <math.h>

using namespace std;

vector<vector<pair<int, int> > > edges;
map<int, int> branch;
vector<int> tree;
vector<int> apples;
vector<int> levels;

void new_edge(int from, int to, int num) {
  pair<int, int> edge = pair<int, int>(to, num);
  if (branch.find(from) != branch.end()) {
    int id = branch.find(from)->second;
    edges[id].push_back(edge);
  } else {
    int id = edges.size();
    vector<pair<int, int> > v;
    v.push_back(edge);
    edges.push_back(v);
    branch.insert(pair<int, int> (from, id));
  }
}

int get_edge(int from, int to) {
  if (branch.find(from) != branch.end()) {
    int id = branch.find(from)->second;
    for (int i = 0; i < edges[id].size(); i++) {
      if (edges[id][i].first == to) return edges[id][i].second;
    }
  }
  return 0;
}

void convert_tree(int start_id) {
  if (branch.find(start_id) == branch.end()) return;
  int id = branch.find(start_id)->second;
  int new_id = (start_id - 1) * 3;
  for (int i = 0; i < edges[id].size(); i++)
    if (branch.find(edges[id][i].first) != branch.end()) {
      int id2 = branch.find(edges[id][i].first)->second;
      int new_id2 = ((edges[id][i].first - 1) * 3);
      tree[new_id + i + 1] = edges[id][i].first ;
      apples[new_id + i + 1] = get_edge(start_id, edges[id][i].first);
      for (int j = 0; j < edges[id2].size(); j++)
        if (edges[id2][j].first == start_id) {
          apples[new_id2] = get_edge(start_id, edges[id][i].first);
          edges[id2].erase(edges[id2].begin() + j);
          tree[new_id2] = start_id;
          break;
        }
      convert_tree(edges[id][i].first);
    }
}

int main (int argc, char **argv) {
  int N, Q, from, to, num;
  scanf("%d %d", &N, &Q);
  tree = vector<int>((N + 1) * 3, -1);
  apples = vector<int>((N + 1) * 3, 0);
  int cur_max[N + 1][N + 1];
  for (int i = 0; i < N - 1; i++) {
    scanf("%d %d %d", &from, &to, &num);
    new_edge(from, to, num);
    new_edge(to, from, num);
  }
  convert_tree(1);

  for (int j = 1; j <= N; j++) {
    cur_max[j][0] = 0;
    cur_max[j][1] = apples[(j - 1) * 3];
  }
  for (int i = 2; i <= Q + 1; i++) {
    for (int j = 0; j < N; j++) {
      int node_id = j;
      int max_val = 0;
      int id1 = tree[node_id * 3 + 1];
      int id2 = tree[node_id * 3 + 2];
      if ((id1 != -1) && (id2 != -1)) {
        for (int k = 0; k <= i - 1; k++) {
          int cur_left_q = i - k - 1;
          if ((cur_max[id1][cur_left_q] + cur_max[id2][k]) > max_val) {
            max_val = cur_max[id1][cur_left_q] + cur_max[id2][k];
          }
        }
      }
      cur_max[node_id + 1][i] = max_val + cur_max[node_id + 1][1];
    }
  }
  printf("%d\n", cur_max[1][Q + 1]);
  return 0;
}

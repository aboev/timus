#include <stdio.h>  
#include <vector>
#include <math.h>
 
using namespace std;  

const int log_tag = false;
//const int log_tag = true;

vector<vector<int>* > g;
vector<int> cache;
vector<bool> isRoot;
vector<int> conv;

int get_conv_sum (bool incl, int id) {
  if (cache[incl ? id * 2 : id * 2 + 1] != -1)
    return cache[incl ? id * 2 : id * 2 + 1];
  int sum = 0;
  if (incl) {
    sum = conv[id];
    for (int i = 0; i < g[id]->size(); i++)
      sum += get_conv_sum(false, (*g[id])[i]);
  } else {
    for (int i = 0; i < g[id]->size(); i++)
      sum += max(get_conv_sum(false, (*g[id])[i]), 
	get_conv_sum(true, (*g[id])[i]));
  }
  cache[incl ? id * 2 : id * 2 + 1] = sum;
  return sum;
}

int main (int argc, char **argv) {
  int N, L, K;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    int r;
    scanf("%d", &r);
    conv.push_back(r);
    vector<int>* v = new vector<int>();
    g.push_back(v);
    isRoot.push_back(true);
    cache.push_back(-1);
    cache.push_back(-1);
  }
  cache.push_back(-1);
  scanf("%d %d", &L, &K);
  while ((L != 0) && (K != 0)) {
    g[K - 1]->push_back(L - 1);
    isRoot[L - 1] = false;
    scanf("%d %d", &L, &K);
  }
  int max = 0, cur = 0;
  for (int i = 0; i < g.size(); i++)
    if (isRoot[i]) {
      cur = get_conv_sum(false, i);
      if (cur > max) max = cur;
      cur = get_conv_sum(true, i);
      if (cur > max) max = cur;
    }
  printf("%d\n", max);
  return 0;
} 

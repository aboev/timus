#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int gsize = 100000;

typedef vector<int> vi;
vi graph[gsize][2];
map<int,int> edge_map;
//map<int,int> marked;
vector<int> marked;

bool log = false;

int edge_count = 0;

bool new_edge(int from, int to, bool rel) {
  bool res = false;
  int from_enc, to_enc;
  if (edge_map.find(from - 1) == edge_map.end()) {
    from_enc = edge_count;
    edge_map.insert(pair<int,int>(from - 1, edge_count));
    edge_count++;
  } else {
    from_enc = edge_map.find(from - 1)->second;
  }
  if (edge_map.find(to) == edge_map.end()) {
    to_enc = edge_count;
    edge_map.insert(pair<int,int>(to, edge_count));
    edge_count++;
  } else {
    to_enc = edge_map.find(to)->second;
    res = true;
  }
  graph[from_enc][rel].push_back(to_enc);
  graph[to_enc][rel].push_back(from_enc);
  return res;
}

int check_cycle_from(int cur_node, int cur_len, int prev_node) {
  if (log) printf("Checking cycle, jumped to %d from %d, marked size = %d \n", cur_node, prev_node, marked.size());
  if (marked[cur_node] != -1) {
    if (log) printf("Found cycle of length %d \n", cur_len);
    return cur_len - marked[cur_node];
  } else {
    marked[cur_node] = cur_len;
    //marked.insert(pair<int,int>(cur_node, cur_len));
    if (log) printf("Node %d, has %d edges \n", cur_node,  graph[cur_node][0].size() + graph[cur_node][1].size());
    for (int i = 0; i < graph[cur_node][0].size(); i++) {
      if (graph[cur_node][0][i] != prev_node) {
        if (log) printf("Jumping to %d, marked size = %d, cur_len = %d \n", graph[cur_node][0][i], marked.size(), cur_len);
        int r = check_cycle_from(graph[cur_node][0][i], cur_len, cur_node);
        if ((r != -1) && (r % 2 == 1)) return r;
      } else {
        if (log) printf("Cannot go to %d \n", prev_node);
      }
    }
    for (int i = 0; i < graph[cur_node][1].size(); i++) {
      if (graph[cur_node][1][i] != prev_node) {
        if (log) printf("Jumping to %d, marked size = %d, cur_len + 1 = %d \n", graph[cur_node][1][i], marked.size(), cur_len + 1);
        int r = check_cycle_from(graph[cur_node][1][i], cur_len + 1, cur_node);
        if ((r != -1) && (r % 2 == 1)) return r;
      } else {
        if (log) printf("Cannot go to %d \n", prev_node);
      }
    }
    return -1; 
  }
}

int main(int argc, char * argv[]) {
  int len, count, from, to;
  char str[27];
  char buf[27];
  //gets(line);
  int gg = 0;
#ifndef ONLINE_JUDGE
   //log = true;
   //freopen("input.txt", "rt", stdin);
   //freopen("output.txt", "wt", stdout);
#endif
  int res;
  int i=0;
  vector<int> results;
  while (true) {
    if (scanf("%d", &len) != 1) return 0;
    //printf("Length = %d \n", len);
    if (len == -1) break;
    if (scanf("%d", &count) != 1) return 0;

    for (int i=0; i<gsize; i++){
      graph[i][0].clear();
      graph[i][1].clear();
    }
    edge_map.clear();
    res = count;
    edge_count=0;
    //printf("Rules count = %d \n", count);
    for (int i = 0; i < count; i++){
      if (scanf("%d %d %4s", &from, &to, str) != 3) return 0;
      if (log) printf("Rule: %d %d %s\n", from, to, str);
      char rel;
      if (strcmp(str, "even")) {
        rel = 1;
      } else {
        rel = 0;
      }
      //bool exist = (graph[to][0].size() > 0) || (graph[to][1].size() > 0);
      //bool exist = to >= from ? new_edge(from, to, rel) : false;
      new_edge(from, to, rel);
      //graph[from-1][rel].push_back(to);
      //printf("Setting graph[%d][%d] new value %d \n", from-1, rel, to);
      //graph[to][rel].push_back(from-1);
      //printf("Setting graph[%d][%d] new value %d \n", to, rel, from-1);
      if ((res == count)) {
	marked.assign(edge_count, -1);;
        int to_enc = edge_map.find(to)->second;
        int l = check_cycle_from(to_enc, 0, -1);
        if((l > 0) && ( l % 2 == 1)) {
  	  res = i;
            //printf("Found cycle after rule %d \n", res);
	    //break;
	}
        //}
      }
    }
    //g.printGraph();
    printf("%d\n", res); 
  }
  return 0;
}

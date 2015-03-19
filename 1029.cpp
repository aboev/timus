#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>

using namespace std;

int **cost_opt;
int **room_opt;
int M, N;

bool log_tag = false;
//bool log_tag = true;

int bound = 1000000000;

int* cost_tmp;

void add_floor(int* cost, int level) {
  for (int i = 0; i < N; i++) {
    int min = (cost_opt[level - 1][i] + cost[i]) > bound ? bound : cost_opt[level - 1][i] + cost[i];
    int min_room = i, sum = cost[i];
    for (int j = i - 1; j >= 0; j = j - 1) {
      if (sum > bound) break;
      sum = sum + cost[j];
      if ( (sum + cost_opt[level - 1][j]) < min ) {
        min = (sum + cost_opt[level - 1][j]) > bound ? bound : sum + cost_opt[level - 1][j];
        min_room = j;
      }
    }
    sum = cost[i];
    for (int j = i + 1; j < N; j++) {
      if (sum > bound) break;
      sum = sum + cost[j];
      if ( (sum + cost_opt[level - 1][j]) < min ) {
        min = (sum + cost_opt[level - 1][j]) > bound ? bound : sum + cost_opt[level - 1][j];
        min_room = j;
      }
    }
    cost_tmp[i] = min;
    room_opt[level][i] = min_room;
    cost_opt[level][i] = cost_tmp[i]; 
  }
}

int main (int argc, char **argv) {
  int n;
  scanf("%d %d", &M, &N);
  cost_opt = (int**) malloc(sizeof(int*) * M);
  room_opt = (int**) malloc(sizeof(int*) * M);
  cost_tmp = (int*) malloc(sizeof(int*) * N);
  for (int i = 0; i < M; i++) {
    cost_opt[i] = (int*) malloc(sizeof(int) * N);
    room_opt[i] = (int*) malloc(sizeof(int) * N);
  }
  for (int i = 0; i*M < N*M; i++) { 
    scanf("%d", &n); 
    cost_opt[0][i] = n; 
    room_opt[0][i] = -1;
  }
  int *cost = (int*) malloc(sizeof(int*) * N);
  for (int i = 1; i < M; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &n);
      cost[j] = n;
    }
    add_floor(cost, i);
  }
  vector<int> res;
  int min = cost_opt[M - 1][0], min_room = 0;
  for (int i = 0; i < N; i++)
    if (cost_opt[M - 1][i] < min) {
      min = cost_opt[M - 1][i];
      min_room = i;
    }
  res.push_back(min_room);
  for (int i = M - 2; i > 0; i = i - 1) {
    int dir = 1;
    if (room_opt[i][min_room] < min_room) dir = -1;
    for (double j = min_room; j != room_opt[i][min_room]; j = j + dir ) res.push_back(j);
    res.push_back(room_opt[i][min_room]);
    min_room = room_opt[i][min_room];
  }
  if (M > 1) res.push_back(min_room);
  reverse(res.begin(), res.end());
  for (int i = 0; i < res.size() - 1; i++) printf("%d ", res[i] + 1);
  printf("%d", res[res.size() - 1] + 1);
  return 0;
}

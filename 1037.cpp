#include <stdio.h>  
#include <string.h>  
#include <vector>
#include <stdlib.h> 
#include <math.h>
#include <algorithm>
 
using namespace std;  

const int log_tag = false;
//const int log_tag = true;

int free_pt = 0;
int prev_tm = -1;
vector<bool> bl(30000, false);
vector<int> tm(30000, 0);

bool read(int id, int timestamp) {
  return bl[id] && ((timestamp - tm[id]) < 600) && (tm[id] = timestamp);
}

int alloc(int timestamp) {
  if (((prev_tm == -1) || (prev_tm == timestamp)) && (free_pt < 30000)) {
    bl[free_pt] = true;
    tm[free_pt] = timestamp;
    free_pt++;
    prev_tm = timestamp;
    return free_pt - 1;
  }
  for (int i = 0; i < bl.size(); i++) {
    if (!bl[i] || ((timestamp - tm[i]) >= 600)) {
      bl[i] = true;
      tm[i] = timestamp;
      return i;
    }
  }
  return -1;
}

int main (int argc, char **argv) {
  char c;
  int t;
  while (scanf("%d %c", &t, &c) != EOF) {
    if (c == '.') {
      int id;
      scanf("%d", &id);
      if (log_tag) printf("read request for %d\n", id);
      printf("%c\n", read(id - 1, t) ? '+' : '-');
    } else {
      if (log_tag) printf("alloc request\n");
      int id = alloc(t);
      printf("%d\n", id != -1 ? id + 1 : '-');
    }
  }
  return 0;
} 

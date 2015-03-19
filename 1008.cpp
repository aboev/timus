#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

const int size = 11 ;

bool input[size][size];
bool marked[size][size];

const char R = 'R';
const char T = 'T';
const char L = 'L';
const char B = 'B';

int main(int argc, char** argv) {
  bool log = false;
  //bool log = true;
  int len=0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      input[i][j] = false;
      marked[i][j] = false;
    }
  }
  int x0, y0;
  char buf[50];
  gets(buf);
  if (sscanf(buf, "%d %d", &x0, &y0) == 1) {
    len = x0;
    scanf("%d %d", &x0, &y0);
    input[x0][y0] = true;
    for (int i = 1; i < len; i++) { 
      int x, y;
      scanf("%d %d", &x, &y);
      input[x][y] = true;
    }
    printf("%d %d\n", x0, y0);
    queue<pair<int,int> > queue;
    queue.push(pair<int,int>(x0,y0));
    marked[x0][y0] = true;
    while (queue.size() > 0 ) {
      pair<int,int> coord = queue.front();
      int x = coord.first;
      int y = coord.second;
      queue.pop();
      //printf("popping %d %d\n", x,y );
      marked[x][y]=true;
      if ((x < size)&&(!marked[x+1][y]) && (input[x+1][y])) {
        printf("%c", R);
        queue.push(pair<int,int>(x+1,y));
        marked[x+1][y]=true;
      }
      if ((y < size)&&(!marked[x][y+1]) && (input[x][y+1])) {
        printf("%c", T);
        queue.push(pair<int,int>(x,y+1));
        marked[x][y+1]=true;
      }
      if ((x > 0 )&&(!marked[x-1][y]) && (input[x-1][y])) {
        printf("%c", L);
        queue.push(pair<int,int>(x-1,y));
        marked[x-1][y]=true;
      }
      if ((y > 0)&&(!marked[x][y-1]) && (input[x][y-1])) {
        printf("%c", B);
        queue.push(pair<int,int>(x,y-1));
        marked[x][y-1]=true;
      }
      if (queue.size() == 0) printf(".\n");
      else printf(",\n");
    }
  } else {
    input[x0][y0] = true;
    queue<pair<int,int> > queue;
    queue.push(pair<int,int>(x0,y0));
    string s;
    char inp[10];
    int count = 1;
    while (queue.size() > 0) {
      pair<int,int> coord = queue.front();
      queue.pop();
      x0 = coord.first;
      y0 = coord.second;
      scanf("%10s", inp);
      s = inp;
      if (s.find(R)!=string::npos) {
        queue.push(pair<int,int>(x0 + 1,y0));
        input[x0 + 1][y0] = true;
        count++;
      }
      if (s.find(T)!=string::npos) {
        queue.push(pair<int,int>(x0,y0 + 1));
        input[x0][y0 + 1] = true;
        count++;
      }
      if (s.find(L)!=string::npos) {
        queue.push(pair<int,int>(x0 - 1,y0));
        input[x0 - 1][y0] = true;
        count++;
      }
      if (s.find(B)!=string::npos) {
        queue.push(pair<int,int>(x0,y0 - 1));
        input[x0][y0 - 1] = true;
        count++;
      }
    }
    printf("%d\n", count); 
    for (int i = 1; i < size - 1; i++){
      for (int j = 1; j < size - 1; j++){
        if (input[i][j]) printf("%d %d\n", i,j); 
      }
    }
  }
}


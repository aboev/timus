#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

void roll_left(unsigned short int vec[6]) {
  char tmp = vec[2]; vec[2] = vec[3]; vec[3] = vec[4]; vec[4] = vec[5]; vec[5] = tmp; vec[1] = vec[1]; vec[0] = vec[0]; }
void roll_right(unsigned short int vec[6]) {
  char tmp = vec[3]; vec[3] = vec[2]; vec[2] = vec[5]; vec[5] = vec[4]; vec[4] = tmp; vec[0] = vec[0]; vec[1] = vec[1]; }
void roll_forward(unsigned short int vec[6]) {
  char tmp = vec[1]; vec[1] = vec[2]; vec[2] = vec[0]; vec[0] = vec[4]; vec[4] = tmp; vec[3] = vec[3]; vec[5] = vec[5]; }
void roll_back(unsigned short int vec[6]) {
  char tmp = vec[1]; vec[1] = vec[4]; vec[4] = vec[0]; vec[0] = vec[2]; vec[2] = tmp; vec[3] = vec[3]; vec[5] = vec[5]; }
void turn_flat(unsigned short int vec[6]) {
  char tmp = vec[3]; vec[3] = vec[1]; vec[1] = vec[5]; vec[5] = vec[0]; vec[0] = tmp; vec[4] = vec[4]; vec[2] = vec[2]; }

bool logflag = false;

unsigned short int* clone_dice(unsigned short int vec[6]) {
  unsigned short int *res = new unsigned short int[6];
  for (int i = 0; i < 6; i++) res[i] = vec[i];
  return res;
}

unsigned short int* roll_until(unsigned short int vec[6], char side) {
  unsigned short int *res = clone_dice(vec);
  if (side == 0) {roll_back(res);}
  else if (side == 1) {roll_forward(res);}
  else if (side == 2) {roll_forward(res); roll_forward(res);}
  else if (side == 3) {roll_right(res);}
  else if (side == 5) {roll_left(res);}
  return res;
}

const short int side = 8, size = 10000;

const int MAX_VAL = 9999999;

unsigned short get_id(unsigned short x, unsigned short y, unsigned short down_side, unsigned short front_side) {
  return y*1000 + x*100 + down_side*10 + front_side;
}

char* get_code(int id) {
  char front_side = id % 10;
  char down_side = ((id - front_side) % 100) / 10;
  char x = ((id - front_side - down_side * 10) % 1000) / 100;
  char y = id / 1000;
  char *res = new char[5];
  res[0] = 'a' + x - 1;
  res[1] = y + '0';
  return res;
}

typedef pair<unsigned short, unsigned short> edge_pair;
typedef vector<unsigned short>* vertex_list_pt;
typedef map<unsigned short, vertex_list_pt > edges_map;
map<edge_pair, unsigned short> gr;
map<unsigned short, vertex_list_pt > edges;

void new_edge(unsigned short from, unsigned short to, unsigned short weight) {
  vertex_list_pt vpt;
  if (edges.find(from) != edges.end()) {
    vpt = edges.find(from)->second;
    if (find(vpt->begin(), vpt->end(), to) == vpt->end()) {
      vpt->push_back(to);
    }
  }else{
    vpt = new vector<unsigned short>();
    vpt->push_back(to);
    edges.insert(pair<unsigned short, vertex_list_pt>(from, vpt));
  }
  if (find(vpt->begin(), vpt->end(), from) == vpt->end()) {
    vpt->push_back(from);
    gr.insert(pair<edge_pair, unsigned short>(edge_pair(from, from), 0));
  }
  if (gr.find(pair<unsigned short, unsigned short>(from, to)) == gr.end()) {
    gr.insert(pair<edge_pair, unsigned short>(edge_pair(from, to), weight));
  }
}

int minDistance(int* dist, bool sptSet[], int size)
{
   int min = MAX_VAL, min_index;

   typedef edges_map::iterator it;
   for(it iterator = edges.begin(); iterator != edges.end(); iterator++) {
     unsigned short v = iterator->first;
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
   }

   return min_index;
}

void dijkstra(int** graph, int *dist, int *prev, int src) {
     bool sptSet[size];

     typedef edges_map::iterator it;
     for(it iterator = edges.begin(); iterator != edges.end(); iterator++) {
       unsigned short i = iterator->first;
       dist[i] = MAX_VAL, sptSet[i] = false, prev[i] = i;
     }

     dist[src] = 0;
     int max_count = edges.size();
     for (int count = 0; count < max_count-1; count++)
     {
       int u = minDistance(dist, sptSet, size);
       sptSet[u] = true;
       for(it iterator = edges.begin(); iterator != edges.end(); iterator++) {
         unsigned short v = iterator->first;
         int wei = MAX_VAL;
         map<edge_pair, unsigned short>::iterator find_res;
         if ( (find_res = gr.find(edge_pair(u, v))) != gr.end()) wei = find_res->second;
         if (!sptSet[v] && dist[u] != MAX_VAL
                                       && dist[u]+wei < dist[v]) {
            dist[v] = dist[u] + wei;
            prev[v] = u;
         }
       }
     }
}

void make_graph(int** graph, int* dist, int* prev, unsigned short dice[]) {
  unsigned short *cur_dice, *next_dice, tmp_dice[6], next_id, cur_id;
  unsigned short destx, desty, destside;
  for (int i = 0; i < 6; i++) tmp_dice[i] = i;
  for (int x = 1; x <= side; x++) {
    for (int y = 1; y <= side; y++) {
      for (int s = 0; s < 6; s++) {
        cur_dice = roll_until(tmp_dice, s);
       for (int d = 0; d < 4; d++) {
        cur_id = get_id(x, y, s, cur_dice[0]);
        if (x > 1) {
          destx = x - 1;
          desty = y;
          next_dice = clone_dice(cur_dice);
          roll_left(next_dice);
          destside = next_dice[4];
          next_id = get_id(destx, desty, destside, next_dice[0]);
          new_edge(cur_id, next_id, dice[next_dice[4]]);
          if (logflag) printf("Rolling left from %d to %d to %d \n", cur_id, next_id, dice[next_dice[4]]);
        }
        if (x < 8) {
          destx = x + 1;
          desty = y;
          next_dice = clone_dice(cur_dice);
          roll_right(next_dice);
          destside = next_dice[4];
          next_id = get_id(destx, desty, destside, next_dice[0]);
          new_edge(cur_id, next_id, dice[next_dice[4]]);
          if (logflag) printf("Rolling right from %d to %d to %d \n", cur_id, next_id, dice[next_dice[4]]);
        }
        if (y < 8) {
          destx = x;
          desty = y + 1;
          next_dice = clone_dice(cur_dice);
          roll_forward(next_dice);
          destside = next_dice[4];
          next_id = get_id(destx, desty, destside, next_dice[0]);
          new_edge(cur_id, next_id, dice[next_dice[4]]);
          if (logflag) printf("Rolling forward from %d to %d to %d \n", cur_id, next_id, dice[next_dice[4]]);
        }
        if (y > 1) {
          destx = x;
          desty = y - 1;
          next_dice = clone_dice(cur_dice);
          roll_back(next_dice);
          destside = next_dice[4];
          next_id = get_id(destx, desty, destside, next_dice[0]);
          new_edge(cur_id, next_id, dice[next_dice[4]]);
          if (logflag) printf("Rolling backward from %d to %d to %d \n", cur_id, next_id, dice[next_dice[4]]);
        }
        turn_flat(cur_dice);
       }
      }
    }
  }
}

int main (int argc, char **argv) {
  int sum = 0;
  char f[2], t[2];
  unsigned short int n[6], from, to;
  int** graph, *dist, *prev;
  map<int, pair<int, int> > gr;
  vector<int> vertex;
  
  scanf("%c%c %c%c %hd %hd %hd %hd %hd %hd\n", &f[0], &f[1], &t[0], &t[1], &n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
  //init_graph(graph, dist, prev);
  dist = new int[size];
  prev = new int[size];
  make_graph(graph, dist, prev, n);
  from = get_id(f[0] - 'a' + 1, f[1] - '0', 4, 0);
  dijkstra(graph, dist, prev, from);
  int min_dist = MAX_VAL, min_dest;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      to = get_id(t[0] - 'a' + 1, t[1] - '0', i, j);
      if (logflag) printf("checking dist from %d to %d is %d\n", from, to, dist[to] + n[4]);
      if ((edges.find(to) != edges.end()) && ((dist[to] + n[4]) < min_dist)) {
        min_dist = dist[to] + n[4];
        min_dest = to;
      }
    }
  }
  string res;
  int next_node = prev[min_dest];
  printf("%d ", min_dist);
  res = string(get_code(min_dest));
  while (next_node != from) {
    if (logflag) printf("%d %s\n", next_node, get_code(next_node));
    else res = string(get_code(next_node)) + " " + res;
    next_node = prev[next_node];
  }
  if (logflag) printf("%d %s\n", next_node, get_code(next_node));
  else res = string(get_code(next_node)) + " " + res;
  printf("%s\n", res.c_str());
  return 0;
}

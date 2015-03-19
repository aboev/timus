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

vector < vector < pair<int,int> > > g;
map<int, int> id_map;
map<int, int> reverse_id_map;
int maxid = 0;

int get_node_index(int id) {
  if (id_map.find(id) != id_map.end()) return id_map.find(id)->second;
  else return -1;
}

int get_node_id(int id) {
  if (reverse_id_map.find(id) != reverse_id_map.end()) return reverse_id_map.find(id)->second;
  else return -1;
}

void new_edge(unsigned short from, unsigned short to, unsigned short weight) {
  int idfrom, idto;
  if (id_map.find(to) == id_map.end()) {
    idto = maxid;
    id_map.insert(pair<int,int>(to, idto));
    reverse_id_map.insert(pair<int,int>(idto, to));
    vector<pair<int, int> > v;
    g.push_back(v);
    //printf("inserting %d with code %d, size = %d \n", maxid, to, g.size());
    maxid++;
  } else {
    idto = id_map.find(to)->second;
  }
  if (id_map.find(from) == id_map.end()) {
    idfrom = maxid;
    id_map.insert(pair<int,int>(from, idfrom));
    reverse_id_map.insert(pair<int,int>(idfrom, from));
    vector<pair<int, int> > v;
    v.push_back(pair<int, int> (idto, weight));
    g.push_back(v);
    //printf("inserting %d with code %d, size = %d \n", maxid, from, g.size());
    maxid++;
  } else {
    idfrom = id_map.find(from)->second;
    g[idfrom].push_back(pair<int, int>(idto, weight));
  }
}

void dijkstra(vector<int> *d, vector<int> *p, int src) {
  int sz = id_map.size();
  (*d)[src] = 0;
  vector<char> u (sz);
  for (int i=0; i<sz; ++i) {
    int v = -1;
    for (int j=0; j<sz; ++j)
      if (!u[j] && (v == -1 || (*d)[j] < (*d)[v]))
        v = j;
    if ((*d)[v] == MAX_VAL)
      break;
    u[v] = true;

    for (size_t j = 0; j < g[v].size(); ++j) {
      int to = g[v][j].first, len = g[v][j].second;
      if ((*d)[v] + len < (*d)[to]) {
        (*d)[to] = (*d)[v] + len;
        (*p)[to] = v;
      }
    }
  }
}

void make_graph(unsigned short dice[]) {
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
  unsigned short int n[6];
  int from, to;
  vector<int> *dist, *prev;
  
  scanf("%c%c %c%c %hd %hd %hd %hd %hd %hd\n", &f[0], &f[1], &t[0], &t[1], &n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
  //init_graph(graph, dist, prev);
  make_graph(n);
  int sz = id_map.size();
  dist = new vector<int>(sz, MAX_VAL);
  prev = new vector<int>(sz);

  from = get_node_index(get_id(f[0] - 'a' + 1, f[1] - '0', 4, 0));
  dijkstra(dist, prev, from);
  int min_dist = MAX_VAL, min_dest;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      to = get_node_index(get_id(t[0] - 'a' + 1, t[1] - '0', i, j));
      if (logflag) printf("checking dist from %d to %d is %d\n", from, to, (*dist)[to] + n[4]);
      if ((to != -1) && (((*dist)[to] + n[4]) < min_dist)) {
        min_dist = (*dist)[to] + n[4];
        min_dest = to;
      }
    }
  }
  string res;
  int next_node = (*prev)[min_dest];
  //printf("min_dest = %d, code = %d min_dist = %d, next_node = %d \n", min_dest, get_node_id(min_dest), min_dist, next_node);
  printf("%d ", min_dist);
  res = string(get_code(get_node_id(min_dest)));
  while (next_node != from) {
    if (logflag) printf("%d %s\n", next_node, get_code(next_node));
    else res = string(get_code(get_node_id(next_node))) + " " + res;
    next_node = (*prev)[next_node];
  }
  if (logflag) printf("%d %s\n", next_node, get_code(next_node));
  else res = string(get_code(get_node_id(next_node))) + " " + res;
  printf("%s\n", res.c_str());
  return 0;
}

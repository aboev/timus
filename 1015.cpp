#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void shift_x(char vec[6]) {
  char tmp = vec[0];
  vec[0] = vec[5];
  vec[5] = vec[1];
  vec[1] = vec[3];
  vec[3] = tmp;
  vec[2] = vec[2];
  vec[4] = vec[4];
}

void shift_y(char vec[6]) {
  char tmp = vec[3];
  vec[3] = vec[2];
  vec[2] = vec[5];
  vec[5] = vec[4];
  vec[4] = tmp;
  vec[0] = vec[0];
  vec[1] = vec[1];
}

int make_int(char vec[6]) {
  int res = 0;
  int pow = 1;
  for (int j = 0; j < 6; j++) {
    res = res + vec[j] * pow; 
    pow = pow * 10;
  }
  return res;
}

int main (int argc, char **argv) {
  int N, dice;
  char n[6], m, t;
  bool rot_y;
  scanf("%d\n", &N);
  map<int, vector<int> > dices;
  vector<int> list;
  for (int i = 0; i < N; i++) {
    int j = 0;
    scanf("%c %c %c %c %c %c\n", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
    m = 0; while ((n[3] != '6') && (m++ < 5)) shift_y(n);
    m = 0; while ((n[0] != '6') && (m++ < 5)) shift_x(n);
    t = n[1] == '5' ? '4' : '5';
    m = 0; while ((n[2] != t) && (m++ < 5)) shift_y(n);
    dice = make_int(n);
    if (dices.find(dice) != dices.end()) {
      dices.find(dice)->second.push_back(i + 1);
    } else {
      vector<int> new_vec;
      new_vec.push_back(i + 1);
      dices.insert(pair<int, vector<int> >(dice, new_vec));
      list.push_back(dice);
    }
  }
  printf("%d\n", list.size());
  for (int i = 0; i < list.size(); i++) {
    for (int j = 0; j < dices.find(list[i])->second.size(); j++) printf("%d ", dices.find(list[i])->second[j]);
    printf("\n");
  }
  return 0;
}

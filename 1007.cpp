#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  bool log = false;
  //bool log = true;
  int len;
  char inp[1002];
  string s;
  scanf("%d", &len);
  //getline(cin, s);
  //while (scanf("%1001s", inp) == 1) {
  while (scanf("%1001s", inp) != EOF) {
  //while (true){
    //getline(cin, s);
    s = inp;
    int modulo = len + 1;
    //if (s == EOF) break;
    if (s.size() == 0) continue;
    s.erase(remove_if( s.begin(), s.end(), ::isspace ), s.end() );
    //s = inp;
    int r = 1, rsd = 0, residue = 0, count = 0, pos = -1, val = 0;
    for (int i = 0 ; i < s.size(); i++) {
      if (s[i] == '1') rsd = (rsd + r) % modulo;
      r++;
    }
    if (log) printf("Initial residue = %d\n", rsd);
    if ((rsd == 0)&&(s.size() == len) ) {
     printf("%s\n",s.c_str());
     continue;
    }
    r = 0;
    if (s.size() < len) {
      for (int i = s.size() + 1; i >= 0; i--) {
        r =  i % modulo;
        if ((i < s.size() + 1) && (s[i - 1] == '1')) {
          residue = (residue + r) % modulo;
          count = (count + 1) % modulo;
        }
        if (log) printf("Residue at position %d is %d\n", i, residue);
        if (log) printf("Residue after inserting 0 is %d(count) + %d(rsd) mod %d = %d\n", count, rsd, modulo, (count + rsd) % modulo );
        if (log) printf("Residue after inserting 1 is %d(count) + %d(r) + %d(rsd) mod %d = %d\n", count, r, rsd, modulo, (count + r + rsd) % modulo);
        if ((count + rsd) % modulo == 0) {
          pos = i - 1;
          val = 0;
          break;
        } else if ((count + r + rsd) % modulo == 0) {
          pos = i - 1;
          val = 1;
          break;
        }
        //r++;
      }
      if (pos != -1) {
        string res = s;
        if (pos <= res.size()) {
          if (val == 1) res.insert(pos, "1");
  	  else res.insert(pos, "0");
        } else {
          res = res + (val == 1? "1" : "0");
        }
        printf("%s\n", res.c_str());
      }
    } else if (s.size() > len) {
      for (int i = s.size(); i > 0; i--) {
        r = i % modulo;
        if (s[i-1] == '1') {
          residue = (residue + r) % modulo;
          count = (count + 1) % modulo;
        }
        if (log) printf("Residue at position %d is %d\n", i, residue);
        if ((s[i-1] == '0')&&((rsd - count) % modulo == 0)) {
          pos = i - 1;
          if (log) printf("Residue after removing digit is %d\n", (rsd - count) % modulo );
          break;
        } else if ((s[i-1] == '1')&&((rsd - count + 1 - r) % modulo == 0)) {
          pos = i - 1;
          if (log) printf("Residue after removing digit is %d\n", (rsd - count + 1 - r) % modulo );
          break;
        }
      }
      if (pos != -1) {
        string res = s;
        if (val == 1) res.insert(pos, "1");
        else res.erase(pos, 1);
        printf("%s\n", res.c_str());
      }
    } else {
      for (int i = s.size(); i > 0; i--) {
        if (log) printf("Residue after replacing 1 to 0 at %d is  %d\n", i, (rsd - i) % modulo );
        if ((s[i-1] == '1')&&((rsd - i) % modulo == 0)) {
          pos = i;
          break;
        }
      }
      if (pos != -1) {
        string res = s;
        res[pos-1] = '0';
        printf("%s\n", res.c_str());
      }
    }
  }
}


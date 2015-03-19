#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stack>

using namespace std;

int main(int argc, char * argv[]) {
  double m;
  stack<double> s;
  while (scanf("%lf", &m) != EOF) {
    s.push(m);
  }
  while (!s.empty()){
    printf("%.4f\n", sqrt(s.top()));
    s.pop();
  }
}

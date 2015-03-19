#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

const char INT_EXP_OP = 0;
const char INT_EXP_CL = 1;
const char INT_COM_OP = 3;
const char INT_COM_CL = 4;
const char INT_UNDEF = 5;
const char INT_NONE = 6;

const char IN_EXP = 0;
const char IN_COM = 1;
const char IN_CODE = 2;

//bool log_tag = true;
bool log_tag = false;

string input;

string SYMB_EXP = "=+-*/0123456789)(";

int get_state(vector<char> *stack) {
  if (stack->size() == 0) return IN_CODE;
  else if (stack->back() == INT_EXP_OP) return IN_EXP;
  else if (stack->back() == INT_COM_OP) return IN_COM;
  else return -1;
}

int is_delim(int pos, int state) {
  string tmp = input.substr(pos, 3);
  if (tmp.find("(*") == 0) return INT_COM_OP;
  else if (tmp.find("*)") == 0) return INT_UNDEF;
  else if ((tmp.find(")") == 0) && (state != IN_COM)) return INT_EXP_CL;
  else if ((tmp.find("(") == 0) && (state != IN_COM)) return INT_EXP_OP;
  else return INT_NONE;
}

bool parse() {
  int pos = 0;
  char state = IN_CODE;
  vector<char> stack;
  while (pos < input.size()) {
    if (log_tag) printf("Currently at pos %d symbol %s state = %s\n", pos, input.substr(pos, 2).c_str(), 
      state==IN_EXP?"expression":(state==IN_CODE?"code":"comment"));
    char flag = is_delim(pos, state);
    if ((flag == INT_NONE) && (state == IN_EXP) && (SYMB_EXP.find(input.at(pos)) == string::npos)) {
      if (log_tag) printf("False on 1 branch\n");
      return false;
    } else if (flag == INT_COM_OP) {
      if (log_tag) printf("Opening comment\n");
      if (state != IN_COM) {stack.push_back(INT_COM_OP); pos++;}
      state = IN_COM; 
    } else if (flag == INT_EXP_OP) {
      if (log_tag) printf("Opening expression\n");
      state = IN_EXP; 
      stack.push_back(INT_EXP_OP);
    } else if ((flag == INT_EXP_CL) && (stack.size() > 0) && (stack.back() == INT_EXP_OP)) {
      if (log_tag) printf("Closing expression\n");
      stack.pop_back(); 
      state = get_state(&stack); 
      if (state == -1) {if (log_tag) printf("State = -1, breaking \n"); return false;}
    } else if ((flag == INT_UNDEF) && (stack.size() > 0) && (stack.back() == INT_COM_OP)) {
      if (log_tag) printf("Closing comment\n");
      stack.pop_back(); 
      state = get_state(&stack); 
      if (state == -1) {if (log_tag) printf("State = -1, breaking \n"); return false;}
      pos++;
    } else if ((flag == INT_UNDEF) && (stack.size() > 0) && (stack.back() == INT_EXP_OP)) {
      if (log_tag) printf("Closing expression\n");
      stack.pop_back();
      state = get_state(&stack);
      pos++;
      if (state == -1) {if (log_tag) printf("State = -1, breaking \n"); return false;}
    } else if (flag != INT_NONE) {
      if (log_tag) printf("Breaking on else case\n");
      return false;
    }
    pos++;
  }
  if (stack.size() > 0) return false;
  return true;
}

int main (int argc, char **argv) {
  for (string line; getline(cin, line);) {
    input = input + line;
  }
//  printf("%s\n", input.c_str());
  bool valid = parse();
  printf("%s\n", valid ? "YES" : "NO");
  return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

int max_length = 50001;

bool sortByLength(const string &lhs, const string &rhs) { return lhs.length() < rhs.length(); }

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

string convert(string from) {
  string input = from;
  replaceAll(input, "i", "1"); replaceAll(input, "j", "1");
  replaceAll(input, "a", "2"); replaceAll(input, "b", "2"); replaceAll(input, "c", "2");
  replaceAll(input, "d", "3"); replaceAll(input, "e", "3"); replaceAll(input, "f", "3");
  replaceAll(input, "g", "4"); replaceAll(input, "h", "4");
  replaceAll(input, "k", "5"); replaceAll(input, "l", "5");
  replaceAll(input, "m", "6"); replaceAll(input, "n", "6");
  replaceAll(input, "p", "7"); replaceAll(input, "r", "7"); replaceAll(input, "s", "7");
  replaceAll(input, "t", "8"); replaceAll(input, "u", "8"); replaceAll(input, "v", "8");
  replaceAll(input, "w", "9"); replaceAll(input, "x", "9"); replaceAll(input, "y", "9");
  replaceAll(input, "o", "0"); replaceAll(input, "q", "0"); replaceAll(input, "z", "0");
  return input;
}

vector<string> find(string input, vector<string> words, int cur_min) {
  vector<string> res;
  if ((cur_min == 1) || (input.length() / max_length > cur_min)) return res;
/*
  for (int i = 0; i < words.size(); i++) {
    size_t start_pos = 0;
    if ((start_pos = input.find(words[i], input.length() - words[i].length())) != std::string::npos) {
      res.push_back(words[i]);
    }
  }
*/
  //printf("Fitting %d words in %s min = %d \n", res.size(), input.c_str(), cur_min);
  sort(res.begin(), res.end(), sortByLength);
  int min = cur_min;
  vector<string> cur_words;
  vector<string> min_words;
  //for (int i = 0; i < res.size(); i++) {
  for (int i = 0; i < words.size(); i++) {
   size_t start_pos = 0;
   if ((start_pos = input.find(words[i], input.length() - words[i].length())) != std::string::npos) {
    //if (res[i].length() == input.length()) {
    if (words[i].length() == input.length()) {
      min = 1;
      min_words.clear();
      //min_words.push_back(res[i]);
      min_words.push_back(words[i]);
      break;
    } else if ( (min > 2) &&
		//((cur_words = find(input.substr(0, input.length() - res[i].length()), words, min - 1)).size() < min - 1 )
		((cur_words = find(input.substr(0, input.length() - words[i].length()), words, min - 1)).size() < min - 1 )
		&& (cur_words.size() > 0)) {
      min = cur_words.size() + 1;
      min_words = cur_words;
      //min_words.push_back(res[i]);
      min_words.push_back(words[i]);
      //printf("New min = %d \n", min);
    } else if (min == 2 ) {
      break;
    }
   }
  }
  return min_words;
}

int main(int argc, char * argv[]) {
  char phone[1000];
  vector<string> words;
  map<string, string> words_dict;
  //gets(line);
  while (gets(phone) && strcmp(phone, "-1")){
    int num;
    scanf("%d", &num);
    //printf("size = %d\n", num);
    words.resize(num);
    cin.ignore();
    for (int i = 0; i < num; i++){
      getline(cin, words[i]);
      words_dict.insert(pair<string, string>(convert(words[i]), words[i]));
      printf("%d: %s %s\n", i, convert(words[i]).c_str(), words[i].c_str());
      words[i] = convert(words[i]);
      if (words[i].length() > max_length) {
        max_length = words[i].length();
      }
    }
/*
    vector<string> words_extra;
    int size = words.size();
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        for (int k = 0; k < size; k++) {
          string extra_word = words[i] + words[j] + words[k];
          words_extra.push_back(extra_word);
          string decode_extra = words_dict.find(words[i])->second + " " + words_dict.find(words[j])->second 		+  " " + words_dict.find(words[k])->second;
          words_dict.insert(pair<string, string>(extra_word, decode_extra));
          printf("Adding extra word %s %s \n", extra_word.c_str(), decode_extra.c_str());
        }
      }
    }
    words = words_extra;
*/
    sort(words.begin(), words.end(), sortByLength);
    vector<string> res_words = find(string(phone), words, string(phone).length());
    string res;
    if (res_words.size() == 0){
      printf("No solution.\n");
    }else{
      res =  words_dict.find(res_words[0])->second;
      for (int i = 1; i < res_words.size(); i++) {
        res = res + " " +  words_dict.find(res_words[i])->second;
      }
      printf("%s\n", res.c_str());
    }
    //printf("Res words count = %d: %s \n", res_words.size(), res.c_str());
  }
}

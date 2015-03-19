#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

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

void find_opt(string input, vector<int>& opt, vector<int>& min_len, vector<string>& words) {
  for (int i = 0; i < input.length(); i++) {
    //printf("Finding opt for end position %d in %s\n", i, input.c_str());
    int min = input.length() + 1;
    for (int j = 0; j < words.size(); j++) {
      int pos = i - words[j].length();
      bool match = pos >= -1 ? input.substr(pos + 1, words[j].length()) == words[j] : false;
      if ((pos > -1) && match) {
        //if ((opt.size() > pos + 1) && (opt[pos+1] > -1)) printf("Comparing end word %s with optimum at %d which is %s\n", words[j].c_str(), pos, words[opt[pos]].c_str());
        if (min_len[pos] + 1 < min) {
          min = min_len[pos] + 1;
          min_len[i] = min_len[pos] + 1;
          opt[i] = j;
          //printf("Optimum at %d is %s\n", i, words[j].c_str());
        }
      } else if ((pos == -1) && match) {
        opt[i] = j;
        min_len[i] = 1;
        min = 1;
        break;
        //printf("Optimum at %d is %s\n", i, words[j].c_str());
      }
    }
  }
}

int main(int argc, char * argv[]) {
  char phone[102];
  char str[52];
  //gets(line);
  vector<string> words;
  map<string, string> words_dict;
  vector<int> opt;
  vector<int> min_len;
  while (true) {
    gets(phone);
    if (!strcmp(phone,"-1")) break;
    int num;
    words.clear();
    words_dict.clear();
    scanf("%d", &num);
    getchar();
    //printf("size = %d\n", num);
    words.resize(num);
    //cin.ignore();
    for (int i = 0; i < num; i++){
      gets(str);
      words[i] = string(str);
      string word_encode = convert(words[i]);
      words_dict.insert(pair<string, string>(word_encode, words[i]));
      //printf("%d: %s %s\n", i, convert(words[i]).c_str(), words[i].c_str());
      words[i] = word_encode;
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
    //sort(words.begin(), words.end(), sortByLength);

    opt.clear();
    min_len.clear();
    for (int i = 0; i < string(phone).length(); i++) {
      opt.push_back(-1);
      min_len.push_back(string(phone).length() + 1);
    }

    find_opt(string(phone), opt, min_len, words); 
    //vector<string> res_words = find(string(phone), words, string(phone).length());
    string res;
    int pos = string(phone).length() - 1;
/*
    for (int i = 0; i < opt.size(); i++){
      if (opt[i] != -1) {
        printf("Optimum word at %d is %s, min_len = %d\n", i, words_dict.find(words[opt[i]])->second.c_str(), min_len[i]);}
      else{
        printf("Optimum word at %d is not found \n", i);
      }
    } 
*/
    while (pos >= 0) {
      if ((opt.size() <= pos) || (opt[pos] == -1)) {
        //printf("No optimum word at %d\n", pos);
        printf("No solution.\n");
        break;
      }
      //printf("Optimum word at %d is id %d \n", pos, opt[pos]);
      res = words_dict.find(words[opt[pos]])->second + " " + res;
      pos = pos - words[opt[pos]].length();
    }
    if ( res.length() > 0 ) {
      res = res.substr(0, res.length() - 1);
      printf("%s\n", res.c_str());
    }
    //printf("Res words count = %d: %s \n", res_words.size(), res.c_str());
  }
  return 0;
}

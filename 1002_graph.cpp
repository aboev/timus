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

using namespace std;

class Vertex;

class Edge
{
  public:
    Edge(Vertex *org, Vertex *dest, int dist)
    {
        origin = org;
        destination = dest;
        distance = dist;
    }

    Vertex* getOrigin() {return origin;}
    Vertex* getDestination() {return destination;}
    int getDistance() {return distance;}
private:
    Vertex* origin;
    Vertex* destination;
    int distance;
};


class Vertex
{
public:
    Vertex(int vertex_id)
    {
        id = vertex_id;
    }

    void addEdge(Vertex *v, int dist)
    {
        Edge newEdge(this, v, dist);
        edges.push_back(newEdge);
        //printf("Creating new edge from %d to %d with dist = %d \n", id, v->getId(), dist);
    }

    void printEdges()
    {
        cout << id << ":" << endl;
        for (int i = 0; i < edges.size(); i++)
        {
        Edge e = edges[i];
        cout << e.getDestination()->getId() <<
            " - " << e.getDistance() << endl;
        }
        cout << endl;
    }

    vector<int> getEdgeWeights(){
      vector<int> res;
      for (int i = 0; i < edges.size(); i++)
      {
        Edge e = edges[i];
        res.push_back(e.getDistance());
      }
      return res;
    }

    int getEdge(Vertex* destination) {
      int res = -1;
      for (int i = 0; i < edges.size(); i++)
      {
        if (edges[i].getDestination() == destination) return i;
      }
      return res;
    }

    void dropEdge(int i) {
      edges.erase(edges.begin() + i);
    }

    int getId() {return id;} 
    vector<Edge> getEdges() {return edges;}

private:
    int id;
    vector<Edge> edges;
};


class Graph
{
public:
    Graph() {}

    void insert(Vertex *v)
    {
        vertices.push_back(v);
    }

    void printGraph()
    {
        for (int i = 0; i < vertices.size(); i++)
            vertices[i]->printEdges();
    }

    Vertex* getVertice(int id) {
      bool res = false;
      for (int i = 0; i < vertices.size(); i++) {
        if ( vertices[i]->getId() == id ) {
          return vertices[i];
        }
      }
      return 0;
    }

    vector<Vertex*> getVertices() {
      return vertices;
    }

private:
    vector<Vertex*> vertices;
};


bool sortByLength(const string &lhs, const string &rhs) { return lhs.length() < rhs.length(); }

Graph buildGraph(string phone, vector<string> words) {
  Graph g;
  for (int i = 0; i < words.size(); i++) {
    for (int j = 0; j <= phone.length() - words[i].length(); j++) {
      //printf("Checking %s against %s \n", phone.substr(j, words[i].length()).c_str(), words[i].c_str());
      if (phone.substr(j, words[i].length()).compare(words[i]) == 0) {
        Vertex *vp_src = g.getVertice(j);
        Vertex *vp_dest =  g.getVertice(j + words[i].length() - 1);
        if (vp_src == 0) {
          vp_src = new Vertex(j); 
  	  g.insert( vp_src );
        }
        if (vp_dest == 0) {
	  vp_dest = new Vertex(j + words[i].length() - 1);
	  g.insert( vp_dest ); 
        }
        //printf("New edge from %d to %d with dist = %d \n", vp_src->getId(), j + words[i].length() - 1, i);
        vp_src->addEdge(vp_dest, i);
      }
    }
  }
  return g;
}

void optimizeGraph(Graph g) {
  vector<Vertex*> vertices = g.getVertices();
  for (int i = 0; i < vertices.size(); i++) {  
    for (int j = 0; j < vertices.size(); j++) {
      for (int k = 0; k < vertices.size(); k++) {
	int id1 = vertices[i]->getEdge(vertices[j]);
	int id2 = vertices[j]->getEdge(vertices[k]);
	int id3 = vertices[i]->getEdge(vertices[k]);
        if ((i != j) && ( j != k) && (i != k) && (id1 != -1) && (id2 != -1) && (id3 != -1)) { 
	  vertices[i]->dropEdge(id1);
	  vertices[i]->dropEdge(id2);
	}
      }
    }
  }
}

int doDfs(Vertex* v, vector<int>& cur_path, int end, int min) {
/*
  printf("Checking vertex %d \n", v->getId());
  printf("min: %d\n", min);
  printf("end: %d\n", end);
  printf("cur_path:\n");
  for (int i = 0; i < cur_path.size(); i++) {
    printf("%d \n",cur_path[i]);
  }
*/
  if ((min > 1) && (v->getId() == end)) {
    //vector<int> new_path = cur_path;
    //printf("Found min \n");
    return cur_path.size();
  } else if (cur_path.size() < min){
    vector<Edge> edges = v->getEdges();
    vector<int> min_path;
    for (int i = 0; i < edges.size(); i++) {
      vector<int> tmp_path = cur_path;
      tmp_path.push_back(edges[i].getDistance());
      int new_size = doDfs(edges[i].getDestination(), tmp_path, end, min );
      if ((new_size < min ) &&
	  (new_size > 0) ) {
        min = new_size;
        min_path = tmp_path;
      }
    }
    cur_path = min_path;
    return min;
  } else {
    //vector<int> min_path;
    return 0;
  }
}

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
    //sort(words.begin(), words.end(), sortByLength);
    //vector<string> res_words = find(string(phone), words, string(phone).length());
    Graph g = buildGraph(string(phone), words);
    for (int i = 0; i < 50; i++){
      optimizeGraph(g);
      printf("optimize %d \n", i);
    }
    //g.printGraph();
    Vertex* v = g.getVertice(0);
    vector<int> res_words;
    if (v != 0) {
      vector<int> path;
      doDfs(v, path, string(phone).length() - 1, 50001);
      res_words = path;
    }
    string res;
    if (res_words.size() == 0){
      printf("No solution.\n");
    }else{
      res =  words_dict.find(words[res_words[0]])->second;
      for (int i = 1; i < res_words.size(); i++) {
        res = res + " " +  words_dict.find(words[res_words[i]])->second;
      }
      printf("%s\n", res.c_str());
    }
    //printf("Res words count = %d: %s \n", res_words.size(), res.c_str());
  }
}

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 2147483647;
const double PI =  3.1415926535897932384626433832795;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define len(x) x.size()
// #define count(arr, elem) count(arr.begin(), arr.end(), elem)
#define in(arr, elem) find(arr.begin(), arr.end(), elem) != arr.end()
#define notin(arr, elem) find(arr.begin(), arr.end(), elem) == arr.end()
#define sum(arr) accumulate(arr.begin(), arr.end(), 0)
#define printVector(arr) for (auto elem : arr) cout << elem << " "; cout << endl;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;
typedef vector<vector<string>> vvs;
typedef vector<vector<char>> vvc;
typedef map<string, int> msi;
typedef map<string, string> mss;
typedef vector<pair<int, int>> vpi;


vector<bool> visited;

// returns number of nodes in one component
// if we want to find all components, keep running this on different roots until
// all nodes are visited
int dfs(int node, map<int, vi> &graph) {
    int visCount = 1;
    visited[node] = true;
    for (auto neighbour: graph[node]) {
        if (!visited[neighbour]) {
            visCount += dfs(neighbour, graph);
        }
    }
    return visCount;
}

// finds all components in a graph
vvi findComponents(map<int, vi> graph, int n) {
  vvi components;
  vb visited(n, false);
  rep(i, 1, n+1) {
    if (!visited[i]) {
      vi component;
      stack<int> s;
      s.push(i);
      while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (!visited[node]) {
          visited[node] = true;
          component.push_back(node);
          for (auto neighbor : graph[node]) {
            s.push(neighbor);
          }
        }
      }
      components.push_back(component);
    }
  }
  return components;
}

// checks if a graph is complete
bool isComplete(map<int, vi> graph, int n) {
  vb visited(n+1, false);
  queue<int> q;
  q.push(1);
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    visited[node] = true;
    for (auto neighbor : graph[node]) {
      if (!visited[neighbor]) {
        q.push(neighbor);
      }
    }
  }
  rep(i, 1, n+1) {
    if (!visited[i]) {
      return false;
    }
  }
  return true;
}


// finds all cycles in a graph
vvi findCycles(map<int, vi> graph, int n) {
  vvi cycles;
  vb visited(n+1, false);
  rep(i, 1, n+1) {
    if (!visited[i]) {
      vi cycle;
      stack<int> s;
      s.push(i);
      while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (!visited[node]) {
          visited[node] = true;
          cycle.push_back(node);
          for (auto neighbor : graph[node]) {
            s.push(neighbor);
          }
        }
      }
      if (len(cycle) > 2) {
        cycles.push_back(cycle);
      }
    }
  }
  return cycles;
}
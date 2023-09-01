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


// colours all components in a graph w/ 1 and 2
// outputs empty vector if not bipartite
// else, outputs vector of colours for each node
// IMPORTANT: assumes each node is in the range 1-n
vi colourNodes(map<int, vi> graph, vvi components, int n) {
  vi colours(n+1, 0);
  trav(component, components) {
    int root = component[0];
    colours[root] = 1;
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
      int node = q.front();
      q.pop();
      for (auto neighbor : graph[node]) {
        if (colours[neighbor] == 0) {
          colours[neighbor] = colours[node] == 1 ? 2 : 1;
          q.push(neighbor);
        } else if (colours[neighbor] == colours[node]) {
          return vi();
        }
      }
    }
  }
  return colours;
}

// returns true if graph is bipartite
bool isBipartite(map<int, vi> adj, int n) {
  vector<int> side(n, -1);
  bool is_bipartite = true;
  queue<int> q;
  for (int st = 1; st < n+1; ++st) {
      if (side[st] == -1) {
          q.push(st);
          side[st] = 0;
          while (!q.empty()) {
              int v = q.front();
              q.pop();
              for (int u : adj[v]) {
                  if (side[u] == -1) {
                      side[u] = side[v] ^ 1;
                      q.push(u);
                  } else {
                      is_bipartite &= side[u] != side[v];
                  }
              }
          }
      }
  }
  return is_bipartite;
}


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

// Counting the number of subtrees rooted at each node
map<int, vi> adj;
map<int, int> subtreeSize;

void dfs(int node, int parent) {
  subtreeSize[node] = 1;
  for (int child : adj[node]) {
    if (child != parent) {
      dfs(child, node);
      subtreeSize[node] += subtreeSize[child];
    }
  }
}

// Diameter of tree
int diameter(map<int, vi> adj) {
  int n = adj.size();
  int diameter = 0;
  function<int(int, int)> dfs = [&](int node, int parent) {
    int maxDepth1 = 0;
    int maxDepth2 = 0;
    for (int child : adj[node]) {
      if (child != parent) {
        int depth = dfs(child, node);
        if (depth > maxDepth1) {
          maxDepth2 = maxDepth1;
          maxDepth1 = depth;
        } else if (depth > maxDepth2) {
          maxDepth2 = depth;
        }
      }
    }
    diameter = max(diameter, maxDepth1 + maxDepth2);
    return maxDepth1 + 1;
  };
  dfs(0, -1);
  return diameter;
}

// For each node, the maximum distance to any other node in the tree
vi firstMax, secondMax, c;   // to store first-max length.

// calculate for every node x the maximum
// length of a path that goes through a child of x
void dfs(int v, int p) {
	firstMax[v] = 0;
	secondMax[v] = 0;
	for (auto x : adj[v]) {
		if (x == p) continue;
		dfs(x, v);
		if (firstMax[x] + 1 > firstMax[v]) {
			secondMax[v] = firstMax[v];
			firstMax[v] = firstMax[x] + 1;
			c[v] = x;
		} else if (firstMax[x] + 1 > secondMax[v]) {
			secondMax[v] = firstMax[x] + 1;
		}
	}
}

// calculate for every node x the
// maximum length of a path through its parent p
void dfs2(int v, int p) {
	for (auto x : adj[v]) {
		if (x == p) continue;
		if (c[v] == x) {
			if (firstMax[x] < secondMax[v] + 1) {
				secondMax[x] = firstMax[x];
				firstMax[x] = secondMax[v] + 1;
				c[x] = v;
			} else {
				secondMax[x] = max(secondMax[x], secondMax[v] + 1);
			}
		} else {
			secondMax[x] = firstMax[x];
			firstMax[x] = firstMax[v] + 1;
			c[x] = v;
		}
		dfs2(x, v);
	}
}

vi getMaxes(map<int, vi> adj, int n) {
  firstMax.resize(n);
  secondMax.resize(n);
  c.resize(n);
  dfs(1, -1);
  dfs2(1, -1);
  return firstMax;
}


// Lowest Common Ancestor
int LCA(map<int, vi> adj, int a, int b) {
  if (a == b) {
    return a;
  }
  int n = adj.size();
  int logn = log2(n);
  vi depth(n);
  vi parent(n);
  vvi dp(n, vi(logn + 1));
  function<void(int, int, int)> dfs = [&](int node, int par, int d) {
    depth[node] = d;
    parent[node] = par;
    for (int child : adj[node]) {
      if (child != par) {
        dfs(child, node, d + 1);
      }
    }
  };
  dfs(0, -1, 0);
  for (int i = 0; i < n; i++) {
    dp[i][0] = parent[i];
  }
  for (int j = 1; j <= logn; j++) {
    for (int i = 0; i < n; i++) {
      if (dp[i][j - 1] != -1) {
        dp[i][j] = dp[dp[i][j - 1]][j - 1];
      }
    }
  }
  if (depth[a] < depth[b]) {
    swap(a, b);
  }
  int k = depth[a] - depth[b];
  for (int i = logn; i >= 0; i--) {
    if (k & (1 << i)) {
      a = dp[a][i];
    }
  }
  if (a == b) {
    return a;
  }
  for (int i = logn; i >= 0; i--) {
    if (dp[a][i] != dp[b][i]) {
      a = dp[a][i];
      b = dp[b][i];
    }
  }
  return parent[a];
}

// Find path between two nodes using DFS
vi findPath(int a, int b) {
  int n = adj.size();
  vi parent(n);
  vb visited(n);
  function<bool(int, int)> dfs = [&](int node, int par) {
    visited[node] = true;
    parent[node] = par;
    if (node == b) {
      return true;
    }
    for (int child : adj[node]) {
      if (!visited[child]) {
        if (dfs(child, node)) {
          return true;
        }
      }
    }
    return false;
  };
  dfs(a, -1);
  vi path;
  for (int node = b; node != -1; node = parent[node]) {
    path.push_back(node);
  }
  reverse(path.begin(), path.end());
  return path;
}
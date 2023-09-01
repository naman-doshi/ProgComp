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
#include <iomanip>
 
using namespace std;
 
const int INF = 2000000000;
const double PI =  3.1415926535897932384626433832795;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define len(x) x.size()
// #define count(arr, elem) count(arr.begin(), arr.end(), elem)
//#define in(arr, elem) find(arr.begin(), arr.end(), elem) != arr.end()
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

vvi generateTable(string a, string b) {
  int n = len(a);
  int m = len(b);
  vvi table(n + 1, vi(m + 1, 0));
  rep(i, 0, n + 1) {
    table[i][0] = i;
  }
  rep(i, 0, m + 1) {
    table[0][i] = i;
  }
  rep(i, 1, n + 1) {
    rep(j, 1, m + 1) {
      if (a[i - 1] == b[j - 1]) {
        table[i][j] = table[i - 1][j - 1];
      }
      else {
        table[i][j] = min(table[i - 1][j - 1], min(table[i - 1][j], table[i][j - 1])) + 1;
      }
    }
  }
  return table;
}

string generateEdits(vvi table, string a, string b) {
  int n = len(a);
  int m = len(b);
  string edits = "";
  while (n > 0 && m > 0) {
    if (a[n - 1] == b[m - 1]) {
      n--;
      m--;
    }
    else {
      if (table[n][m] == table[n - 1][m - 1] + 1) {
        edits += "1";
        n--;
        m--;
      }
      else if (table[n][m] == table[n - 1][m] + 1) {
        edits += "2";
        n--;
      }
      else {
        edits += "3";
        m--;
      }
    }
  }
  while (n > 0) {
    edits += "2";
    n--;
  }
  while (m > 0) {
    edits += "3";
    m--;
  }
  reverse(edits.begin(), edits.end());
  return edits;
}


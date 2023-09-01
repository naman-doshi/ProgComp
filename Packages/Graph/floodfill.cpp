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

// number of connected components of a particular character in a grid
int numComponents(vector<vector<char>> grid, char lookingFor) {
  int row_num = grid.size();
  int col_num = grid[0].size();
  vector<vector<bool>> visited(row_num, vector<bool>(col_num, false));
  int ans = 0;
  for (int i = 0; i < row_num; i++) {
    for (int j = 0; j < col_num; j++) {
      if (!visited[i][j] && grid[i][j] == lookingFor) {
        ans++;
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        while (!q.empty()) {
          pair<int, int> curr = q.front();
          q.pop();
          int curr_row = curr.first;
          int curr_col = curr.second;
          if (curr_row < 0 || curr_row >= row_num || curr_col < 0 || curr_col >= col_num) {
            continue;
          }
          if (visited[curr_row][curr_col]) {
            continue;
          }
          visited[curr_row][curr_col] = true;
          if (grid[curr_row][curr_col] == lookingFor) {
            q.push(make_pair(curr_row + 1, curr_col));
            q.push(make_pair(curr_row - 1, curr_col));
            q.push(make_pair(curr_row, curr_col + 1));
            q.push(make_pair(curr_row, curr_col - 1));
          }
        }
      }
    }
  }
  return ans;
}

vector<vpi> findComponents(vvc grid, char lookingFor) {
  int row_num = grid.size();
  int col_num = grid[0].size();
  vector<vector<bool>> visited(row_num, vector<bool>(col_num, false));
  vector<vpi> ans;
  for (int i = 0; i < row_num; i++) {
    for (int j = 0; j < col_num; j++) {
      if (!visited[i][j] && grid[i][j] == lookingFor) {
        vpi currr;
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        while (!q.empty()) {
          pair<int, int> curr = q.front();
          q.pop();
          int curr_row = curr.first;
          int curr_col = curr.second;
          if (curr_row < 0 || curr_row >= row_num || curr_col < 0 || curr_col >= col_num) {
            continue;
          }
          if (visited[curr_row][curr_col]) {
            continue;
          }
          visited[curr_row][curr_col] = true;
          if (grid[curr_row][curr_col] == lookingFor) {
            currr.push_back(make_pair(curr_row, curr_col));
            q.push(make_pair(curr_row + 1, curr_col));
            q.push(make_pair(curr_row - 1, curr_col));
            q.push(make_pair(curr_row, curr_col + 1));
            q.push(make_pair(curr_row, curr_col - 1));
          }
        }
        ans.push_back(currr);
      }
    }
  }
  return ans;
}

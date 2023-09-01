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

int r, c;

// number of paths to any square in a normal grid
int numPaths(int N, int M) {
  N++; M++;
  vector<vector<int>> dp(N+1, vector<int>(M+1));
  dp[0][0] = 1;
  for (int i = 0; i < M; i++) {
	  for (int j = 0; j < N; j++) {
		  if (j > 0) dp[j][i] += dp[j - 1][i];
		  if (i > 0) dp[j][i] += dp[j][i - 1];
	  }
  }
  return dp[N-1][M-1];
}

// number of paths to any square in a grid, with prohibited squares (walls)
int numPathsWithBlocks(vector<vector<int>> grid) {
  int r = grid.size();
  int c = grid[0].size();
  vector<vector<int>> dp(r+1, vector<int>(c+1));
  dp[0][0] = 1;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (grid[i][j] == 1) dp[i][j] = 0;
			else {
				if (i > 0) dp[i][j] += dp[i - 1][j];
				if (j > 0) dp[i][j] += dp[i][j - 1];
				//dp[i][j] %= 1000000007;
			}
		}
	}
  return dp[r-1][c-1];
}

// longest common subsequence
int longestCommonSubsequence(string a, string b) {
		int dp[a.size()][b.size()];
		for (int i = 0; i < a.size(); i++) { fill(dp[i], dp[i] + b.size(), 0); }
		for (int i = 0; i < a.size(); i++) {
			if (a[i] == b[0]) dp[i][0] = 1;
			if (i != 0) dp[i][0] = max(dp[i][0], dp[i - 1][0]);
		}
		for (int i = 0; i < b.size(); i++) {
			if (a[0] == b[i]) dp[0][i] = 1;
			if (i != 0) dp[0][i] = max(dp[0][i], dp[0][i - 1]);
		}
		for (int i = 1; i < a.size(); i++) {
			for (int j = 1; j < b.size(); j++) {
				if (a[i] == b[j]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				} else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		return dp[a.size() - 1][b.size() - 1];
}



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

map<int, int> succ;
vector<vector<int>> precomp;

void precompute(int U) {
  precomp.resize(succ.size() + 1, vector<int>(U+1, -1));
  int curr = 2;
  for (auto element : succ) {
    precomp[element.first][1] = succ[element.first];
  }
  while (curr < U) {
    for (auto element : succ) {
        precomp[element.first][curr] = precomp[precomp[element.first][curr/2]][curr/2];
    }
    curr *= 2;
  }
}

int getNum(int x, vector<int> powers2) {
  if (powers2.size() == 0) return x;
  int top = powers2.front();
  powers2.erase(powers2.begin());
  return getNum(precomp[x][top], powers2);
}

int successorK(int x, int k) {
  if (k == 1) return succ[x];
  else {
    vector<int> powersOfTwo;
    while (k > 0) {
      int pt = log2(k);
      int biggest = pow(2, pt);
      k -= biggest;
      powersOfTwo.push_back(biggest);
    }
    return getNum(x, powersOfTwo);
  }
}

int cycleLength(int x) {
  int a = succ[x];
  int b = succ[succ[x]];
  while (a != b) {
    a = succ[a];
    b = succ[succ[b]];
  }
  a = x;
  while (a != b) {
    a = succ[a];
    b = succ[b];
  }
  int first = a;
  b = succ[a];
  int length = 1;
  while (a != b) {
    b = succ[b];
    length++;
  }
  return length;
}



int main() {
  succ[1] = 3;
  succ[2] = 5;
  succ[3] = 7;
  succ[4] = 6;
  succ[5] = 2;
  succ[6] = 2;
  succ[7] = 1;
  succ[8] = 6;
  succ[9] = 3;
  precompute(15);
  cout << successorK(4, 11) << endl;
}
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
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

int last_true(int lo, int hi, function<bool(int)> f) {
	// if none of the values in the range work, return lo - 1
	lo--;
	while (lo < hi) {
		// find the middle of the current range (rounding up)
		int mid = lo + (hi - lo + 1) / 2;
		if (f(mid)) {
			// if mid works, then all numbers smaller than mid also work
			lo = mid;
		} else {
			// if mid does not work, greater values would not work either
			hi = mid - 1;
		}
	}
	return lo;
}

int last_true_jump(int lo, int hi, function<bool(int)> f) {
	lo--;
	for (int dif = hi - lo; dif > 0; dif /= 2) {
		while (lo + dif <= hi && f(lo + dif)) { lo += dif; }
	}
	return lo;
}

int first_true(int lo, int hi, function<bool(int)> f) {
  // if none of the values in the range work, return hi + 1
  hi++;
  while (lo < hi) {
    // find the middle of the current range (rounding down)
    int mid = lo + (hi - lo) / 2;
    if (f(mid)) {
      // if mid works, then all numbers greater than mid also work
      hi = mid;
    } else {
      // if mid does not work, smaller values would not work either
      lo = mid + 1;
    }
  }
  return hi;
}

long long f(int x) {
  return x * x;
}

// returns the minimum value of f(x) in the range [low, high]
int minimise(int low, int high) {
  int mid = (low + high) / 2;

  if (mid == low || mid == high) return min(f(mid), f(mid + 1));

  long long d1 = f(mid);
  long long d2 = f(mid);

  if (d1 < d2) {
    return minimise(low, mid);
  } else {
    return minimise(mid, high);
  }

}


int binarySearch(vector<int> arr, int search) {
  int l = 0;
  int r = arr.size() - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    if (arr[m] == search) {
      return m;
    } else if (arr[m] < search) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return -1;
}


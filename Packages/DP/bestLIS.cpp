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


class MaxSegTree {
  private:
	int len;
	vector<int> segtree;

  public:
	MaxSegTree(int len) : len(len), segtree(2 * len) {}

	void set(int ind, int val) {
		for (segtree[ind += len] = val; ind > 1; ind >>= 1) {
			segtree[ind >> 1] = max(segtree[ind], segtree[ind ^ 1]);
		}
	}

	// maximum of the range [from, to)
	int range_max(int from, int to) {
		int max_ = INT32_MIN;
		for (from += len, to += len; from < to; from >>= 1, to >>= 1) {
			if ((from & 1) != 0) { max_ = max(max_, segtree[from++]); }
			if ((to & 1) != 0) { max_ = max(max_, segtree[--to]); }
		}
		return max_;
	}
};

int find_lis(vector<int> a) {
	// apply coordinate compression to all elements of the array
	vector<int> sorted(a);
	sort(sorted.begin(), sorted.end());
	int at = 0;
	map<int, int> coord_comp;
	for (int i : sorted) {
		if (!coord_comp.count(i)) { coord_comp[i] = at++; }
	}
	// cmp(i) gives the compressed version of index i
	auto cmp = [&](int i) -> int { return coord_comp[a[i]]; };

	MaxSegTree dp(coord_comp.size());
	dp.set(cmp(0), 1);
	for (int i = 1; i < a.size(); i++) {
		int max_prev = dp.range_max(0, cmp(i));
		if (max_prev != INT32_MIN) {
			dp.set(cmp(i), max_prev + 1);
		} else {
			dp.set(cmp(i), 1);
		}
	}

	return dp.range_max(0, coord_comp.size());
}

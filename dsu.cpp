#include <iostream>
// Disjoint set
// Time complexity: O(N*A) ~ O(N) (A is some function)

// Notes:
// - fill(p, p+1+n, -1);
// p[u] = k < 0   -->   u is root. Then k is the tree size
// p[u] > 0       -->   u is not root, p[u] is u's parent

using namespace std;
const int N = 1e6 + 7;

struct DSU {
    int p[N];
    DSU (int n) { fill(p, p+1+n, -1); }
    int find(int u) {
        return p[u] < 0 ? u : p[u] = find(p[u]);
    }

    void join(int r, int s) {
        if (p[s] < p[r]) {
            p[s] += p[r];
            p[r] = s;
        }
        else {
            p[r] += p[s];
            p[s] = r;
        }
    }
};



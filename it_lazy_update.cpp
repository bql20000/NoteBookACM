#include <math.h>
#include <iostream>

// Problem: QMAX2 - VNOJ
// Status: Accepted

// Update: increase w at [l..r]
// Query: max(l..r)



using namespace std;
const int N  = 5e4 + 7;
const int INF = 1e9 + 87;

int n, m;

struct IntervalTree {
    int t[4*N], lazy[4*N];
    void down(int x) {
        t[2*x] += lazy[x];
        t[2*x+1] += lazy[x];
        lazy[2*x] += lazy[x];
        lazy[2*x+1] += lazy[x];
        lazy[x] = 0;
    }

    void update(int x, int l, int r, int u, int v, int w) {
        if (v < l || u > r) return;
        if (u <= l && r <= v) {
            t[x] += w;
            lazy[x] += w;
            return;
        }
        down(x);
        int m = (l + r) / 2;
        update(2*x, l, m, u, v, w);
        update(2*x+1, m+1, r, u, v, w);
        t[x] = max(t[2*x], t[2*x+1]);
    }

    int get(int x, int l, int r, int u, int v) {
        if (v < l || u > r) return 0;
        if (u <= l && r <= v) return t[x];
        down(x);
        int m = (l + r) / 2;
        return max(get(2*x, l, m, u, v), get(2*x+1, m+1, r, u, v));
    }
};


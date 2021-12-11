#include <iostream>

using namespace std;
const int N = 1e5 + 7;

struct IntervalTree {
    int t[4*N];

    void update(int x, int l, int r, int i, int v) {
        if (i < l || r < i) return;
        if (l == r) t[x] = v;
        else {
            int mid = (l + r) / 2;
            update(x*2, l, mid, i, v);
            update(x*2+1, mid+1, r, i, v);
            t[x] = max(t[x*2], t[x*2+1]);
        }
    }

    int get(int x, int l, int r, int u, int v) {
        if (v < l || r < u) return 0;
        if (u <= l && r <= v) return t[x];
        int mid = (l + r) / 2;
        return max(get(x*2, l, mid, u, v), get(x*2+1, mid+1, r, u, v));
    }
};
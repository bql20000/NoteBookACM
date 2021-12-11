// Binary Index Tree

const int N = 1e5 + 8;
int n;

struct BIT {
    int s[N];
    void update(int x, int w) {
        for (; x <= n; x += x & -x) s[x] += w;
    }
    int query(int x) {     // query sum(1..x)
        int res = 0;
        for (; x; x -= x & -x) res += s[x];
        return res;
    }
    int query(int l, int r) {   // query sum(l..r)
        return query(r) - query(l-1);
    }
};

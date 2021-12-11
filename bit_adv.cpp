// Status: Accepted 1070C
// Advance part: Find x that sum(1..x) <= limit in log(N)
// Similar idea with finding LCA

const int N = 1e6 + 8;
const int logN = 20;

int n;

struct BIT {
    int s[N];
    void update(int x, int w) {
        for (; x <= n; x += x & -x) s[x] += w;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) res += s[x];
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l-1);
    }
    int findRightMost(int limit) {
        // Binary search approach: O(logN ^ 2)
        int l = 0, h = n+1;
        while (l + 1 < h) {
            int m = (l + h) / 2;
            if (query(m) <= limit) l = m; else h = m;
        } 
        return l;
    }
    int findRightMostVer2(int limit) {  
        // Smarter approach: O(logN)
        int x = 0, nx;
        for (int i = logN; i >= 0; --i) {
            nx = x + (1<<i);
            if (nx <= n && s[nx] <= limit) {
                x = nx;
                limit -= s[nx];
            }
        }
        return x;
    }
};
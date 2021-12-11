#include <iostream>
#include <vector>
#include <algorithm>

// Kruskal then LCA, a complete implementation
// Problem: VOI 11 (6): https://oj.vnoi.info/problem/upgranet
// Status: AC

using namespace std;
const int N = 1e5 + 8;
const int logN = 17;
typedef pair<int,int> ii;

int n, m, p[N][logN+1], d[N], f[N][logN+1];
vector<ii> a[N];

struct Edge {
    int u, v, w;
} e[N];

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

void input() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) 
        cin >> e[i].u >> e[i].v >> e[i].w;
}

void kruskal() {
    sort(e+1, e+1+m, [](Edge &u, Edge &v){ return u.w > v.w; });
    DSU dsu(n);
    for (int i = 1; i <= m; ++i) {
        int r = dsu.find(e[i].u), s = dsu.find(e[i].v);
        if (r != s) {
            dsu.join(r, s);
            // cout << "picked: " << e[i].u << ' ' << e[i].v << endl;
            a[e[i].u].push_back({e[i].v, e[i].w});
            a[e[i].v].push_back({e[i].u, e[i].w});
        }
    }
}

void DFS(int u) {
    for (auto &e : a[u]) {
        int v = e.first, w = e.second;
        if (d[v] == 0) {
            p[v][0] = u;
            f[v][0] = w;
            d[v] = d[u] + 1;
            DFS(v);
        }
    }
}
void initLCA() {
    f[1][0] = 1e9;
    DFS(1);
    for (int k = 1; k <= logN; ++k)
        for (int u = 1; u <= n; ++u) {
            p[u][k] = p[p[u][k-1]][k-1];
            f[u][k] = min(f[u][k-1], f[p[u][k-1]][k-1]);
        }
}

int findThroughput(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    int diff = d[u] - d[v];
    int res = 1e9;
    for (int i = 0; i <= logN; ++i)
        if ((1<<i) & diff) {
            res = min(res, f[u][i]);
            u = p[u][i];
        }
    
    if (u == v) return res;

    // remember to loop from logN -> 0 here
    for (int i = logN; i >= 0; --i) 
        if (p[u][i] != p[v][i]) {
            res = min(res, min(f[u][i], f[v][i]));
            u = p[u][i];
            v = p[v][i];
        }

    return min(res, min(f[u][0], f[v][0]));
}

void solve() {
    long long res = 0;
    for (int i = 1; i <= m; ++i) {
        res += findThroughput(e[i].u, e[i].v) - e[i].w;
    }
    cout << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);  cin.tie(NULL);
    input();
    kruskal();
    initLCA();
    solve();
    return 0;
}


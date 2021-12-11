#include <math.h>
#include <vector>

using namespace std;
const int N = 1e5 + 7;
const int logN = 17;
typedef pair<int,int> ii;

int n, m, p[N][logN+1], d[N], f[N][logN+1];
vector<int> a[N];

void DFS(int u) {
    for (auto v : a[u]) {
        if (d[v] == 0) {
            p[v][0] = u;
            d[v] = d[u] + 1;
            DFS(v);
        }
    }
}

void initLCA() {
    DFS(1);
    for (int k = 1; k <= logN; ++k)
        for (int u = 1; u <= n; ++u) {
            p[u][k] = p[p[u][k-1]][k-1];
        }
}

int jumpUpTree(int u, int dist) {
    // return u's parent after jumping "dist" node upward 
    for (int i = 0; i <= logN; ++i)
        if ((1<<i) & dist) u = p[u][i];
    return u;
}

int findLCA(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    jumpUpTree(u, d[u] - d[v]);
    
    if (u == v) return u;

    // remember to loop from logN -> 0 here
    for (int i = logN; i >= 0; --i) 
        if (p[u][i] != p[v][i]) {
            u = p[u][i];
            v = p[v][i];
        }

    return p[u][0];
}
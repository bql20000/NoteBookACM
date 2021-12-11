#include <vector>
#include <math.h>

// Status: Accepted (TJALG - SPOJ)
// Tarjan algorithm --> find strongly connected components

using namespace std;
const int N = 1e5 + 7;

int n, m, low[N], num[N], timeDFS, scc;
bool deleted[N];
vector<int> a[N], st;

void dfs(int u) {
    st.push_back(u);
    num[u] = low[u] = ++timeDFS;
    for (auto v : a[u]) {
        if (deleted[v]) continue;
        if (!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], num[v]);
    }

    if (low[u] == num[u]) {
        ++scc;
        for (int tmp = -1; tmp != u;) { 
            tmp = st.back();
            st.pop_back();
            deleted[tmp] = true;
        } 
    }
}

void tarjan() {
    scc = 0;    // number of strongly connected components
    timeDFS = 0;
    for (int i = 1; i <= n; ++i)
        if (!num[i]) dfs(i);

    // cout << scc << endl;
}

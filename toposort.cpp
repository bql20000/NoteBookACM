#include <vector>

// status: Accept NKJUMP VOI 2008

// Notes: Trick to check if is DAG or not here:
// https://cowboycoder.tech/article/ly-thuyet-do-thi-co-ban-phan-5-dag-va-sap-xep-topo-tren-do-thi

using namespace std;
const int N = 1007;

int n, nums[N], curTime, order[N];
bool vis[N];
vector<int> a[N];

void dfs(int u) {
    vis[u] = true;
    for (auto v : a[u])
        if (!vis[v]) dfs(v);
    order[curTime--] = u;
}

void Topo() {
    curTime = n;
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) dfs(i);
}


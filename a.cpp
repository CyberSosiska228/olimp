#include <bits/extc++.h>
#define int long long

void dfs(std::vector<std::vector<int>> &g, std::vector<bool> &used, int n) {
    used[n] = true;
    for (int i = 0; i < size(g[n]); i++) {
        if (!used[g[n][i]]) {
            dfs(g, used, g[n][i]);
        }
    }
}


signed main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<bool> used(n, false);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(g, used, i);
            cnt++;
        }
    }

    std::cout << m - n + cnt << '\n';
    return 0;
}

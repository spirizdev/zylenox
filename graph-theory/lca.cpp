const int N = 1e5 + 10;
int par[N][20], h[N];
void dfs(int u, int p = -1) {
    for (int v : adj[u]) if (v != p) {
        h[v] = h[u] + 1;
        par[v][0] = u;
        for (int i = 1; i < 20; i++)
            par[v][i] = par[par[v][i - 1]][i - 1];
        dfs(v, u);
    }
}
int lca(int u, int v) {
    if (h[u] != h[v]) {
        if (h[u] < h[v]) swap(u, v);
        int k = h[u] - h[v];
        for (int j = 0; 1 << j <= k; j++)
            if (bit(j, k)) u = par[u][j];
    }
    if (u == v) return u;
    int k = __lg(h[u]);
    for (int i = k; i >= 0; i--)
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];
    return par[u][0];
}

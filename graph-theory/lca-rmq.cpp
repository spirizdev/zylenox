const int N = 5e5 + 10;
const int LG = 20;
int n, up[LG][N << 1], dep[N];
int st[N], tour[N << 1], timer;
vi adj[N];
void dfs(int u, int p = -1) {
    tour[++timer] = u;
    st[u] = timer;
    for (int v : adj[u]) if (v != p) {
        dep[v] = dep[u] + 1;
        dfs(v, u);
        tour[++timer] = u;
    }
}
#define minDep(x, y) (dep[x] < dep[y] ? x : y)
void build() {
    rep(i, 1, timer) up[0][i] = tour[i];
    rep(i, 1, LG - 1)
        for (int j = 1; j + (1 << i) - 1 <= timer; j++)
            up[i][j] = minDep(up[i - 1][j], up[i - 1][j + (1 << (i - 1))]);
}
int lca(int u, int v) {
    int l = st[u], r = st[v];
    if (l > r) swap(l, r);
    int k = 31 - __builtin_clz(r - l + 1);
    return minDep(up[k][l], up[k][r - (1 << k) + 1]);
}

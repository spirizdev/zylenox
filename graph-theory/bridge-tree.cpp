int n, m, q;
vii adj[N];
int low[N], id[N], cnt = 0;
bool isBridge[N];
int com[N];
vi nadj[N];
int in[N], out[N];
int par[N][20], h[N];
void dfs(int u, int p = -1) {
    low[u] = id[u] = ++cnt;
    for (auto [v, idx] : adj[u]) {
        if (idx != p) {
            if (id[v]) {
                cmin(low[u], id[v]);
            } else {
                dfs(v, idx);
                cmin(low[u], low[v]);
                if (low[v] > id[u])
                    isBridge[idx] = true;
            }
        }
    }
}
void dfs_com(int u) {
    com[u] = cnt;
    for (auto [v, idx] : adj[u])
        if (!com[v] && !isBridge[idx])
            dfs_com(v);
}
void _dfs(int u, int p = -1) {
    in[u] = ++cnt;
    for (int v : nadj[u]) {
        if (v != p) {
            h[v] = h[u] + 1;
            par[v][0] = u;
            for (int i = 1; i < 20; i++)
                par[v][i] = par[par[v][i - 1]][i - 1];
            _dfs(v, u);
        }
    }
    out[u] = cnt;
}
int LCA(int u, int v) {
    if (h[u] != h[v]) {
        if (h[u] < h[v]) swap(u, v);
        int k = h[u] - h[v];
        for (int j = 0; (1 << j) <= k; j++)
            if (bit(j, k)) u = par[u][j];
    }
    if (u == v) return u;
    int k = __lg(h[u]);
    for (int i = k; ~i; i--)
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];
    return par[u][0];
}
int In(int x, int y) {
    return in[x] <= in[y] && in[y] <= out[x];
}
int Get(int x, int y, int z, int t) {
    if (!In(x, z) && !In(z, x)) return 0;
    for (int i = 20 - 1; ~i; i--)
        if (par[t][i] != 0 && !In(par[t][i], y))
            t = par[t][i];
    if (!In(t, y)) t = par[t][0];
    return max(0ll, h[t] - max(h[x], h[z]));
}
void main(void) {
    cin >> n >> m >> q;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
    }
    cnt = 0;
    dfs(1);
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!com[i]) {
            ++cnt;
            dfs_com(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (auto [v, idx] : adj[i]) {
            if (com[i] < com[v]) {
                nadj[com[i]].pb(com[v]);
                nadj[com[v]].pb(com[i]);
            }
        }
    }
    h[1] = 1;
    cnt = 0;
    _dfs(1);
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a = com[a]; b = com[b]; c = com[c]; d = com[d];
        int lcaAB = LCA(a, b);
        int lcaCD = LCA(c, d);
        int ans = h[c] + h[d] - 2 * h[lcaCD];
        ans -= Get(lcaAB, a, lcaCD, c);
        ans -= Get(lcaAB, a, lcaCD, d);
        ans -= Get(lcaAB, b, lcaCD, c);
        ans -= Get(lcaAB, b, lcaCD, d);
        cout << ans << '\n';
    }
}

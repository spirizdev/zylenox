const int N = 40010;
const int M = 100010;
int n, m, a[N], ans[M];
vi adj[N], v;
int st[N], en[N], tour[N << 1], cur = 0;
int par[N][20], h[N];
void dfs(int u, int p = -1) {
    st[u] = ++cur;
    tour[cur] = u;
    for (int v : adj[u]) if (v != p) {
        h[v] = h[u] + 1;
        par[v][0] = u;
        for (int i = 1; i < 20; i++)
            par[v][i] = par[par[v][i - 1]][i - 1];
        dfs(v, u);
    }
    en[u] = ++cur;
    tour[cur] = u;
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
int block[N << 1], vis[N], val[N];
struct query {
    int id, l, r, lc;
    bool operator < (const query &other) {
        return (block[l] == block[other.l]) ? (r < other.r) : (block[l] < block[other.l]);
    }
} qs[M];
void check(int x, int &res) {
    if ((vis[x]) && (--val[a[x]] == 0)) --res;
    else if ((!vis[x]) && (val[a[x]]++ == 0)) ++res;
    vis[x] ^= 1;
}
void main(void) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i], v.pb(a[i]);
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(all(v), a[i]) - v.begin();
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1);
    int size = sqrt(cur);
    for (int i = 1; i <= cur; i++)
        block[i] = (i - 1) / size + 1;
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        qs[i].lc = lca(u, v);
        if (st[u] > st[v]) swap(u, v);
        if (qs[i].lc == u) qs[i].l = st[u], qs[i].r = st[v];
        else qs[i].l = en[u], qs[i].r = st[v];
        qs[i].id = i;
    }
    sort(qs, qs + m);
    int L = qs[0].l, R = qs[0].l - 1, res = 0;
	for (int i = 0; i < m; i++) {
        while (L < qs[i].l) check(tour[R++], res);
        while (L > qs[i].l) check(tour[--R], res);
        while (R < qs[i].r) check(tour[++R], res);
        while (R > qs[i].r) check(tour[R--], res);
        int u = tour[L], v = tour[R];
        if (qs[i].lc != u && qs[i].lc != v) check(qs[i].lc, res);
        ans[qs[i].id] = res;
        if (qs[i].lc != u && qs[i].lc != v) check(qs[i].lc, res);
	}
	for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
}

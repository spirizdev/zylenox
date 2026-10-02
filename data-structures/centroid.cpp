// count number paths with exactly k edges in a tree
const int N = 2e5 + 10;
int n, k, child[N], del[N], cnt[N], ans;
vi adj[N];
void countChild(int u, int p = -1) {
    child[u] = 1;
    each(v, adj[u]) if (v != p && !del[v]) {
        countChild(v, u);
        child[u] += child[v];
    }
}
int centroid(int u, int p, int n) {
    each(v, adj[u])
        if (v != p && child[v] > n / 2 && !del[v])
            return centroid(v, u, n);
    return u;
}
void dfs(int u, int p, int dep, vi &deps) {
    if (dep > k) return;
    deps.pb(dep);
    each(v, adj[u]) if (v != p && !del[v])
        dfs(v, u, dep + 1, deps);
}
void calc(int root, int n) {
    cnt[0] = 1;
    vi used; used.pb(0);
    each(v, adj[root]) if (!del[v]) {
        vi deps;
        dfs(v, root, 1, deps);
        each(d, deps) if (d <= k) ans += cnt[k - d];
        each(d, deps) if (d <= k) {
            if (cnt[d] == 0) used.pb(d);
            ++cnt[d];
        }
    }
    each(x, used) cnt[x] = 0;
}
void solve(int u) {
    countChild(u);
    int n = child[u];
    int root = centroid(u, 0, n);
    // main step: compute from centroid
    calc(root, n);
    del[root] = 1;
    each(v, adj[root]) if (!del[v])
        solve(v);
}
void main(void) {
    cin >> n >> k;
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    solve(1);
    cout << ans << '\n';
}

const int N = 3e5 + 10;
int n, m, indeg[N];
vi g[N], topo;
void main(void) {
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
    }
    queue<int> q;
    rep(i, 1, n) each(v, g[i]) indeg[v]++;
    rep(i, 1, n) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.pb(u);
        each(v, g[u]) {
            indeg[v]--;
            if (indeg[v] == 0)
                q.push(v);
        }
    }
    // check cycle
    assert(sz(topo) == n);
    cout << sz(topo) << '\n';
    each(x, topo) cout << x << ' ';
}

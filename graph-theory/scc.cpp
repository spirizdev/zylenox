const int N = 3e5 + 10;
int n, m, scc, timer;
vi g[N], comp[N];
bool vis[N];
int comp_id[N], tin[N], low[N];
stack<int> st;
void dfs(int u) {
    vis[u] = true;
    tin[u] = low[u] = ++timer;
    st.push(u);
    each(v, g[u]) {
        if (!tin[v]) {
            dfs(v);
            cmin(low[u], low[v]);
        } else if (vis[v]) {
            cmin(low[u], tin[v]);
        }
    }
    if (low[u] == tin[u]) {
        ++scc;
        while (true) {
            int x = st.top(); st.pop();
            vis[x] = false;
            comp_id[x] = scc;
            comp[scc].pb(x);
            if (x == u) break;
        }
    }
}
void main(void) {
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
    }
    rep(i, 1, n) if (!tin[i]) dfs(i);
    cout << scc << '\n';
    rep(i, 1, scc) {
        cout << sz(comp[i]) << ' ';
        each(x, comp[i]) cout << x << ' ';
        cout << '\n';
    }
}

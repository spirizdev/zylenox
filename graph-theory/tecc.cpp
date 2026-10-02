const int N = 3e5 + 10;
int n, m, scc, timer;
vi g[N], t[N];
vii br;
bool vis[N];
int comp[N], tin[N], low[N];
void dfs(int u, int p = -1) {
    vis[u] = 1;
    tin[u] = low[u] = ++timer;
    each(v, g[u]) if (v != p) {
        if (vis[v]) {
            cmin(low[u], tin[v]);
        } else {
            dfs(v, u);
            cmin(low[u], low[v]);
        }
    }
}
void dfs2(int u, int num) {
    comp[u] = num;
    each(v, g[u]) {
        if (comp[v] != -1) continue;
        if (tin[u] < low[v]) {
            br.eb(u, v);
            ++scc;
            dfs2(v, scc);
        } else {
            dfs2(v, num);
        }
    }
}
void build_tree() {
    each(x, br) {
        int u = comp[x.fi], v = comp[x.se];
        t[u].pb(v);
        t[v].pb(u);
    }
}
void main(void) {
    mem(comp, -1);
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    rep(i, 1, n) if (!vis[i]) {
        dfs(i);
        dfs2(i, scc);
        ++scc;
    }
    cout << sz(br) << ' ' << scc << '\n';
}

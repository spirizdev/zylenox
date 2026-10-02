const int N = 5e5 + 10;
const int LG = 20;
int n, up[LG][N << 1], dep[N];
int st[N], tour[N << 1], timer;
vi adj[N], aux[N];
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
    for (int i = 1; i <= timer; i++) up[0][i] = tour[i];
    for (int i = 1; i < LG; i++)
        for (int j = 1; j + (1 << i) - 1 <= timer; j++)
            up[i][j] = minDep(up[i - 1][j], up[i - 1][j + (1 << (i - 1))]);
}
int lca(int u, int v) {
    int l = st[u], r = st[v];
    if (l > r) swap(l, r);
    int k = 31 - __builtin_clz(r - l + 1);
    return minDep(up[k][l], up[k][r - (1 << k) + 1]);
}
void calc_aux(vi &p) {
    if (p.empty()) return;
    sort(all(p), [&](int a, int b) { return st[a] < st[b]; });
    vi stk{1};
    aux[1].clear();
    auto add = [&](int u, int v) {
        aux[u].pb(v);
        aux[v].pb(u);
    };
    for (auto u : p) {
        if (u == 1) continue;
        int l = lca(u, stk.back());
        if (l != stk.back()) {
            while (sz(stk) >= 2 && dep[stk[sz(stk) - 2]] >= dep[l]) {
                add(stk.back(), stk[sz(stk) - 2]);
                stk.pop_back();
            }
            if (stk.back() != l) {
                aux[l].clear();
                add(l, stk.back());
                stk.pop_back();
                stk.pb(l);
            }
        }
        aux[u].clear();
        stk.pb(u);
    }
    while (sz(stk) > 1) {
        add(stk.back(), stk[sz(stk) - 2]);
        stk.pop_back();
    }
}

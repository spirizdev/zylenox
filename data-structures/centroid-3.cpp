const int N = 1e5 + 10;
vi adj[N];
int sz[N], done[N], cenpar[N];
void calc_sz(int u, int p) {
    sz[u] = 1;
    each(v, adj[u]) {
        if (v == p || done[v]) continue;
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}
int find_cen(int u, int p, int k) {
    each(v, adj[u]) {
        if (v == p || done[v]) continue;
        if (sz[v] * 2 > k) return find_cen(v, u, k);
    }
    return u;
}
void solve(int u) {

}
void decompose(int u, int p = -1) {
    calc_sz(u, p);
    int cen = find_cen(u, p, sz[u]);
    cenpar[cen] = p;
    done[cen] = 1;
    solve(cen);
    each(v, adj[cen]) {
        if (v == p || done[v]) continue;
        decompose(v, cen);
    }
}
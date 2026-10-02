int par[N], depth[N], sz[N], pos[N], arr[N];
int chainID[N], chainHead[N];
int curChain, curPos;
void dfs(int u, int p = -1) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        par[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
void hld(int u, int p = -1) {
    if (!chainHead[curChain]) chainHead[curChain] = u;
    chainID[u] = curChain;
    pos[u] = curPos;
    arr[curPos++] = u;
    int nxt = 0;
    for (int v : adj[u]) if (v != p)
        if (nxt == 0 || sz[v] > sz[nxt]) nxt = v;
    if (nxt) hld(nxt, u);
    for (int v : adj[u]) {
        if (v != p && v != nxt) {
            curChain++;
            hld(v, u);
        }
    }
}
int LCA(int u, int v) {
    while (chainID[u] != chainID[v]) {
        if (chainID[u] > chainID[v]) u = par[chainHead[chainID[u]]];
        else v = par[chainHead[chainID[v]]];
    }
    return depth[u] < depth[v] ? u : v;
}
int T[N << 2], lz[N << 2];
// if each node has val[i] -> init(1, 1, n)
void init(int id, int l, int r) {
    if (l == r) {
        T[id] = val[arr[l]];
        return;
    }
    int mid = (l + r) >> 1;
    init(id << 1, l, mid);
    init(id << 1 | 1, mid + 1, r);
    T[id] = T[id << 1] + T[id << 1 | 1];
}
void push(int id, int l, int r) {
    if (lz[id]) {
        int mid = (l + r) >> 1;
        T[id << 1] += lz[id] * (mid - l + 1);
        T[id << 1 | 1] += lz[id] * (r - mid);
        lz[id << 1] += lz[id];
        lz[id << 1 | 1] += lz[id];
        lz[id] = 0;
    }
}
void upd(int id, int l, int r, int u, int v, int val) {
    if (u > r || v < l) return;
    if (u <= l && r <= v) {
        T[id] += val * (r - l + 1);
        lz[id] += val;
        return;
    }
    push(id, l, r);
    int mid = (l + r) >> 1;
    upd(id << 1, l, mid, u, v, val);
    upd(id << 1 | 1, mid + 1, r, u, v, val);
    T[id] = T[id << 1] + T[id << 1 | 1];
}
int get(int id, int l, int r, int u, int v) {
    if (u > r || v < l) return 0;
    if (u <= l && r <= v) return T[id];
    push(id, l, r);
    int mid = (l + r) >> 1;
    return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
}
void upd(int u, int v, int val) {
    while (chainID[u] != chainID[v]) {
        if (depth[chainHead[chainID[u]]] < depth[chainHead[chainID[v]]])
            swap(u, v);
        upd(1, 1, n, pos[chainHead[chainID[u]]], pos[u], val);
        u = par[chainHead[chainID[u]]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    upd(1, 1, n, pos[u], pos[v], val);
}
int get(int u, int v) {
    int res = 0;
    while (chainID[u] != chainID[v]) {
        if (depth[chainHead[chainID[u]]] < depth[chainHead[chainID[v]]])
            swap(u, v);
        res += get(1, 1, n, pos[chainHead[chainID[u]]], pos[u]);
        u = par[chainHead[chainID[u]]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res += get(1, 1, n, pos[u], pos[v]);
    return res;
}
void main(void) {
    cin >> n >> q;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, adj[u].pb(v), adj[v].pb(u);
    curChain = curPos = 1;
    dfs(1);
    hld(1);
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        upd(a, b, 1);
        cout << get(c, d) << '\n';
        upd(a, b, -1);
    }
}

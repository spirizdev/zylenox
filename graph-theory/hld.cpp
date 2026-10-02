// Process XOR path queries and updates in a tree.
int n, q, val[N]; vi adj[N];
int par[N], depth[N], sz[N], pos[N], arr[N];
int chainID[N], chainHead[N];
int curChain, curPos;
// chainID: stores the ID of the chain that vertex u belongs to.
// chainHead: stores the head (first vertex) of the chain with ID chainID.
void dfs(int u, int p = -1) {
    sz[u] = 1;
    for(int v : adj[u]) {
        if(v == p) continue;
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
int T[N << 2];
void init(int node, int l, int r) {
    if (l == r) {
        T[node] = val[arr[l]];
        return;
    }
    int mid = (l + r) >> 1;
    init(node << 1, l, mid);
    init(node << 1 | 1, mid + 1, r);
    T[node] = T[node << 1] ^ T[node << 1 | 1];
}
void update(int node, int l, int r, int pos, int val) {
    if (pos > r || pos < l) return;
    if (l == r && l == pos) {
        T[node] = val;
        return;
    }
    int mid = (l + r) >> 1;
    update(node << 1, l, mid, pos, val);
    update(node << 1 | 1, mid + 1, r, pos, val);
    T[node] = T[node << 1] ^ T[node << 1 | 1];
}
int get(int node, int l, int r, int u, int v) {
    if (u > r || v < l) return 0;
    if (u <= l && r <= v) return T[node];
    int mid = (l + r) >> 1;
    return get(node << 1, l, mid, u, v) ^ get(node << 1 | 1, mid + 1, r, u, v);
}
void update(int x, int val) {
    update(1, 1, n, pos[x], val);
}
int query(int u, int v) {
    int lca = LCA(u, v);
    int ans = 0;
    while (chainID[u] != chainID[lca]) {
        ans ^= get(1, 1, n, pos[chainHead[chainID[u]]], pos[u]);
        u = par[chainHead[chainID[u]]];
    }
    while (chainID[v] != chainID[lca]) {
        ans ^= get(1, 1, n, pos[chainHead[chainID[v]]], pos[v]);
        v = par[chainHead[chainID[v]]];
    }
    if (depth[u] < depth[v]) ans ^= get(1, 1, n, pos[u], pos[v]);
    else ans ^= get(1, 1, n, pos[v], pos[u]);
    return ans;
}
void main(void) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    curPos = curChain = 1;
    dfs(1);
    hld(1);
    init(1, 1, n);
    while (q--) {
        int type, x, val; cin >> type >> x >> val;
        if (type == 1) update(x, val);
        else cout << query(x, val) << '\n';
    }
}

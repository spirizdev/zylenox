// toggle node color and query nearest white node in a tree
const int inf = 0x3f3f3f3f;
const int N = 1e5 + 10;
int n, q, col[N];
int del[N], par[N], child[N];
vi adj[N];
map<int, int> d[N];
multiset<int> s[N];
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
void calc(int u, int p, int root) {
    each(v, adj[u]) if (v != p && !del[v]) {
        d[v][root] = d[u][root] + 1;
        calc(v, u, root);
    }
}
int solve(int u) {
    countChild(u);
    int n = child[u];
    int root = centroid(u, 0, n);
    d[root][root] = 0;
    // main step: compute from centroid
    calc(root, 0, root);
    del[root] = 1;
    each(v, adj[root]) if (!del[v]) {
        int x = solve(v);
        par[x] = root;
    }
    return root;
}
void main(void) {
    cin >> n;
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    solve(1);
    cin >> q;
    while (q--) {
        int op, u; cin >> op >> u;
        if (op == 0) {
            int p = u;
            col[u] ^= 1;
            if (col[u] == 0) {
                while (p) {
                    s[p].erase(s[p].lower_bound(d[u][p]));
                    p = par[p];
                }
            } else {
                while (p) {
                    s[p].insert(d[u][p]);
                    p = par[p];
                }
            }
        } else {
            int ans = inf, p = u;
            while (p) {
                if (!s[p].empty())
                    cmin(ans, d[u][p] + *s[p].begin());
                p = par[p];
            }
            cout << (ans == inf ? -1 : ans) << '\n';
        }
    }
}

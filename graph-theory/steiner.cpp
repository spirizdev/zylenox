const int N = 3e5 + 10;
int n, k, spec[N], isMark[N];
int par[N], preW[N], cnt[N];
vii adj[N]; vi order;
bool inSteiner[N];
void main(void) {
    cin >> n >> k;
    rep(i, 1, n - 1) {
        int u, v, w = 1;
        cin >> u >> v;
        adj[u].eb(v, w);
        adj[v].eb(u, w);
    }
    rep(i, 1, k) {
        cin >> spec[i];
        isMark[spec[i]] = 1;
    }
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.pb(u);
        for (auto [v, w] : adj[u]) if (v != par[u])
            par[v] = u, preW[v] = w, q.push(v);
    }
    rep(i, 1, n) cnt[i] = isMark[i];
    per(i, n - 1, 0) {
        int u = order[i];
        if (par[u] != 0) cnt[par[u]] += cnt[u];
    }
    int sum = 0;
    rep(i, 2, n) if (cnt[i] > 0 && cnt[i] < k) sum += preW[i];
    rep(i, 1, n) if (isMark[i]) inSteiner[i] = 1;
    rep(v, 2, n) if (cnt[v] > 0 && cnt[v] < k)
        inSteiner[v] = inSteiner[par[v]] = 1;
    int cnt = 0;
    rep(i, 1, n) if (inSteiner[i]) ++cnt;
    cout << cnt << '\n';
}

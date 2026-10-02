const int inf = 0x3f3f3f3f;
int n;
vii adj[N];
bool spfa(int s, vi &d) {
    d.assign(n + 1, inf);
    vi cnt(n + 1, 0);
    vector<bool> inqueue(n);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    inqueue[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inqueue[u] = false;
        for (auto e : adj[u]) {
            int v = e.fi, w = e.se;
            if (cmin(d[v], d[u] + w)) {
                d[v] = d[u] + w;
                if (!inqueue[v]) {
                    q.push(v);
                    inqueue[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n)
                        return false;
                }
            }
        }
    }
    return true;
}

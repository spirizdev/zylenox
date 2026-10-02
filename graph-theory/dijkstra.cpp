const int inf = 0x3f3f3f3f3f3f3f3f;
void ijk(int s) {
    vi dist(n + 1, inf); dist[s] = 0;
    priority_queue<pii, vii, greater<pii>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (cmin(dist[v], dist[u] + w))
                pq.emplace(v, dist[v]);
        }
    }
}

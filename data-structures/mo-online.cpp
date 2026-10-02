// update [l, r] : a_l, a_l+1, ... -> a_r, a_r-1, ...
// query [l, r] : nums equal to k
const int N = 1e5 + 10;
const int S = 447;
int n, m, lastAns = 0;
deque<int> a[N / S + 10];
int cnt[N / S + 10][N];
int type, u, v, w;
void decode() {
    u = (u + lastAns - 1) % n;
    v = (v + lastAns - 1) % n;
    if (u > v) swap(u, v);
    if (type == 2)
        w = (w + lastAns - 1) % n + 1;
}
void update(int l, int r) {
    int blockL = l / S, blockR = r / S;
    int tmp = *(a[blockR].begin() + (r % S));
    a[blockR].erase(a[blockR].begin() + (r % S));
    a[blockL].insert(a[blockL].begin() + (l % S), tmp);
    --cnt[blockR][tmp]; ++cnt[blockL][tmp];
    for (int i = blockL; i < blockR; i++) {
        int tmp = a[i].back();
        a[i + 1].push_front(a[i].back());
        a[i].pop_back();
        --cnt[i][tmp];
        ++cnt[i + 1][tmp];
    }
}
int get(int l, int r, int k) {
    int ans = 0;
    while (l <= r) {
        if (l % S == 0 && l + S - 1 <= r) {
            ans += cnt[l / S][k];
            l += S;
        } else ans += (a[l / S][l++ % S] == k);
    }
    return ans;
}
void main(void) {
    cin >> n;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        a[i / S].pb(x);
        ++cnt[i / S][x];
    }
    cin >> m;
    while (m--) {
        cin >> type >> u >> v;
        if (type == 1) {
            decode();
            update(u, v);
        } else {
            cin >> w;
            decode();
            lastAns = get(u, v, w);
            cout << lastAns << '\n';
        }
    }
}

const int N = 1e6 + 10;
const int S = 632;
int n, t, a[N];
struct query {
    int l, r, id;
    bool operator < (const query &other) const {
        if (l / S == other.l / S) return ((l / S) & 1) ? r > other.r : r < other.r;
        return l / S < other.l / S;
    }
} qs[N];
int res[N], cnt[N], ans;
void add(int pos) {
    int x = a[pos];
    ans -= cnt[x] * cnt[x] * x;
    cnt[x]++;
    ans += cnt[x] * cnt[x] * x;
}
void del(int pos) {
    int x = a[pos];
    ans -= cnt[x] * cnt[x] * x;
    cnt[x]--;
    ans += cnt[x] * cnt[x] * x;
}
void main(void) {
    cin >> n >> t;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, t) {
        int l, r;
        cin >> l >> r;
        qs[i] = {l, r, i};
    }
    sort(qs + 1, qs + t + 1);
    int L = 1, R = 0;
    rep(i, 1, t) {
        auto [l, r, id] = qs[i];
        while (L > l) add(--L);
        while (R < r) add(++R);
        while (L < l) del(L++);
        while (R > r) del(R--);
        res[id] = ans;
    }
    rep(i, 1, t) cout << res[i] << '\n';
}

const int N = 300010;
int n, m, k, want[N], st[N], en[N], amount[N], l[N], r[N], ans[N];
vi a[N], mid[N];
struct BIT {
    int n;
    vi ft;
    BIT() {}
    BIT(int _n) {
        n = _n;
        ft.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        for (; i <= n; i += i & -i) ft[i] += val;
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    int get(int i) {
        int ans = 0;
        for (; i; i -= i & -i) ans += ft[i];
        return ans;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
};
void main(void) {
    cin >> n >> m;
    rep(i, 1, m) {
        int x; cin >> x;
        a[x].pb(i);
    }
    rep(i, 1, n) cin >> want[i];
    cin >> k;
    rep(i, 1, k) cin >> st[i] >> en[i] >> amount[i];
    rep(i, 1, n) l[i] = 1, r[i] = k, ans[i] = -1;
    while (1) {
        bool ok = true;
        rep(i, 1, k) mid[i].clear();
        rep(i, 1, n) if (l[i] <= r[i]) mid[(l[i] + r[i]) >> 1].pb(i), ok = false;
        BIT ft(m);
        rep(i, 1, k) {
            if (st[i] <= en[i]) ft.upd(st[i], en[i], amount[i]);
            else ft.upd(1, en[i], amount[i]), ft.upd(st[i], m, amount[i]);
            each(x, mid[i]) {
                int cnt = 0;
                each(y, a[x]) {
                    cnt += ft.get(y);
                    if (cnt >= want[x]) break;
                }
                if (cnt >= want[x]) ans[x] = i, r[x] = i - 1;
                else l[x] = i + 1;
            }
        }
        if (ok) break;
    }
    rep(i, 1, n) {
        if (ans[i] == -1) cout << "NIE\n";
        else cout << ans[i] << '\n';
    }
}

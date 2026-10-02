struct BIT {
    int n;
    vi ft1, ft2;
    BIT() {}
    BIT(int _n) {
        n = _n;
        ft1.assign(n + 1, 0);
        ft2.assign(n + 1, 0);
    }
    void upd(vi &ft, int i, int val) {
        for (; i <= n; i += i & -i) ft[i] += val;
    }
    int get(vi &ft, int i) {
        int ans = 0;
        for (; i; i -= i & -i) ans += ft[i];
        return ans;
    }
    void upd(int l, int r, int val) {
        upd(ft1, l, val);
        upd(ft1, r + 1, -val);
        upd(ft2, l, val * (l - 1));
        upd(ft2, r + 1, -val * r);
    }
    int get(int i) {
        return get(ft1, i) * i - get(ft2, i);
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

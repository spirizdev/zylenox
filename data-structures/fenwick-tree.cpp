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

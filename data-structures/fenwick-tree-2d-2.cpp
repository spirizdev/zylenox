struct BIT2D {
    vvi ft1, ft2, ft3, ft4;
    int m, n;
    BIT2D() {}
    BIT2D(int _m, int _n) : m(_m), n(_n) {
        ft1.assign(m + 1, vi(n + 1, 0));
        ft2.assign(m + 1, vi(n + 1, 0));
        ft3.assign(m + 1, vi(n + 1, 0));
        ft4.assign(m + 1, vi(n + 1, 0));
    }
    void upd(vvi &ft, int x, int y, int val) {
        for (int i = x; i <= m; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                ft[i][j] += val;
    }
    int get(vvi &ft, int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                res += ft[i][j];
        return res;
    }
    void upd(int x1, int y1, int x2, int y2, int val) {
        upd(ft1, x1, y1, val);
        upd(ft1, x1, y2 + 1, -val);
        upd(ft1, x2 + 1, y1, -val);
        upd(ft1, x2 + 1, y2 + 1, val);

        upd(ft2, x1, y1, val * (x1 - 1));
        upd(ft2, x1, y2 + 1, -val * (x1 - 1));
        upd(ft2, x2 + 1, y1, -val * x2);
        upd(ft2, x2 + 1, y2 + 1, val * x2);

        upd(ft3, x1, y1, val * (y1 - 1));
        upd(ft3, x1, y2 + 1, -val * y2);
        upd(ft3, x2 + 1, y1, -val * (y1 - 1));
        upd(ft3, x2 + 1, y2 + 1, val * y2);

        upd(ft4, x1, y1, val * (x1 - 1) * (y1 - 1));
        upd(ft4, x1, y2 + 1, -val * (x1 - 1) * y2);
        upd(ft4, x2 + 1, y1, -val * x2 * (y1 - 1));
        upd(ft4, x2 + 1, y2 + 1, val * x2 * y2);
    }
    int get(int x, int y) {
        return get(ft1, x, y) * x * y - get(ft2, x, y) * y - get(ft3, x, y) * x + get(ft4, x, y);
    }
    int get(int x1, int y1, int x2, int y2) {
        return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
    }
};

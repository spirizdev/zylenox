struct BIT2D {
    vvi ft; int m, n;
    BIT2D() {}
    BIT2D(int m, int n) : ft(m + 1, vi(n + 1)), m(m), n(n) {};
    void upd(int x, int y, int val) {
        for (; x <= m; x += x & -x)
            for (int v = y; v <= n; v += v & -v)
                ft[x][v] += val;
    }
    int get(int x, int y) {
        int res = 0;
        for (; x > 0; x -= x & -x)
            for (int v = y; v > 0; v -= v & -v)
                res += ft[x][v];
        return res;
    }
    int getRange(int x1, int y1, int x2, int y2) {
        return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
    }
};

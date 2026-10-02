const int N = 510, LG = 10;
int m, n, a[N][N], st[LG + 1][N][LG + 1][N];
void process() {
    rep(k, 0, LG) rep(i, 1, m - (1 << k) + 1)
    rep(l, 0, LG) rep(j, 1, n - (1 << l) + 1) {
        if (k == 0) {
            if (l == 0) st[0][i][0][j] = a[i][j];
            else st[0][i][l][j] = min(st[0][i][l - 1][j], st[0][i][l - 1][j + (1 << (l - 1))]);
        } else {
            st[k][i][l][j] = min(st[k - 1][i][l][j], st[k - 1][i + (1 << (k - 1))][l][j]);
        }
    }
}
int query(int x, int y, int a, int b) {
    int k = __lg(a - x + 1), l = __lg(b - y + 1);
    return min({st[k][x][l][y], st[k][x][l][b - (1 << l) + 1],
                st[k][a - (1 << k) + 1][l][y], st[k][a - (1 << k) + 1][l][b - (1 << l) + 1]});
}

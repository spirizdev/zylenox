const int N = 2e5 + 10, LG = 18;
int n, a[N], st[LG + 1][N];
void process() {
    rep(i, 1, n) st[0][i] = a[i];
    rep(j, 1, LG) rep(i, 1, n - (1 << j) + 1)
        st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
}
int query(int l, int r) {
    int k = __lg(r - l + 1);
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}

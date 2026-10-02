const int N = 1010;
int d[N][N];
void main(void) {
    mem(d, 0x3f, sizeof d);
    rep(k, 1, n) rep(i, 1, n) rep(j, 1, n)
        cmin(d[i][j], d[i][k] + d[k][j]);
}

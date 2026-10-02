// the number of elements y such that x | y = x
// the number of elements y such that x & y = x
// the number of elements y such that x & y != 0
const int B = 20;
int a[1 << B], f[1 << B], g[1 << B];
void main(void) {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ++f[a[i]];
        ++g[a[i]];
    }
    for (int i = 0; i < B; i++)
        for (int mask = 0; mask < (1 << B); mask++)
            if ((mask & (1 << i)) != 0)
                f[mask] += f[mask ^ (1 << i)];
    for (int i = 0; i < B; i++)
        for (int mask = (1 << B) - 1 ; mask >= 0 ; mask--)
            if (!bit(i, mask)) g[mask] += g[mask ^ (1 << i)] ;
    for (int i = 1; i <= n; i++)
        cout << f[a[i]] << ' ' << g[a[i]] << ' ' << n - f[(1 << B) - 1 - a[i]] << '\n';
}

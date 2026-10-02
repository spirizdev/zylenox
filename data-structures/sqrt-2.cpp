// count possible black square sets
// N squares using moves from array A
/// i -> i + a[i] * x
void main() {
    int n; cin >> n; vi a(n);
    for (int &x : a) cin >> x;
    int x = sqrt(n);
    vi dp(n, 1); vector<vi> s(x + 1, vi(x + 1));
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] > x) {
            for (int j = i + a[i]; j < n; j += a[i])
                add(dp[i], dp[j]);
        } else {
            add(dp[i], s[a[i]][i % a[i]]);
        }
        for (int j = 1; j <= x; j++)
            add(s[j][i % j], dp[i]);
    }
    cout << dp[0] << '\n';
}

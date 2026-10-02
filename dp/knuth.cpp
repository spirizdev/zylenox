const int N = 1e3 + 10;
int n, a[N], pref[N], dp[N][N], opt[N][N];
void main(void) {
    /// O(n^3)
//    cin >> n;
//    for (int i = 0; i < n; i++)
//        cin >> a[i], pref[i + 1] = pref[i] + a[i];
//    for (int i = n - 2; i >= 0; i--) {
//        for (int j = i + 1; j < n; j++) {
//            int cost = pref[j + 1] - pref[i];
//            dp[i][j] = 2e18;
//            for (int k = i; k < j; k++)
//                cmin(dp[i][j], dp[i][k] + dp[k + 1][j] + cost);
//        }
//    }
//    cout << dp[0][n - 1];
    /// O(n^2) (Knuth's Optimization)
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
        opt[i][i] = i;
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            int cost = pref[j + 1] - pref[i];
            int mn = 2e18;
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                if (mn >= dp[i][k] + dp[k + 1][j] + cost) {
                    opt[i][j] = k;
                    mn = dp[i][k] + dp[k + 1][j] + cost;
                }
            }
            dp[i][j] = mn;
        }
    }
    cout << dp[0][n - 1];
}

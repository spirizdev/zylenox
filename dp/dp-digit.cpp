int a, b, k, x, y; string s;
int dp[20][200][200][2];
int fun(int pos, int sum, int sumDigit, bool tight) {
    if (pos == sz(s)) return sum == 0 && sumDigit == 0;
    if (dp[pos][sum][sumDigit][tight] != -1) return dp[pos][sum][sumDigit][tight];
    int res = 0, lim = tight ? s[pos] - '0' : 9;
    for (int i = 0; i <= lim; i++)
        res += fun(pos + 1, (sum + i) % k, (sumDigit * 10 + i) % k, tight && (i == lim));
    return dp[pos][sum][sumDigit][tight] = res;
}
int cnt = 0;
int calc(int x) {
    s = to_string(x);
    memset(dp, -1, sizeof dp);
    return fun(0, 0, 0, 1);
}
void solve() {
    cin >> a >> b >> k; --a;
    x = calc(a); y = calc(b);
    cout << "Case " << ++cnt << ": " << y - x << '\n';
}

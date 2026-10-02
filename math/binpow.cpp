ll binpow(ll a, ll b, ll MOD) {
    a %= MOD;
    ll res = 1;
    for (; b; b >>= 1, a = a * a % MOD) 
        if (b & 1) res = res * a % MOD;
    return res;
}
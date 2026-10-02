ll fact[N], inv_fact[N];
ll binpow(ll a, ll b, ll MOD) {
    a %= MOD;
    ll res = 1;
    for (; b; b >>= 1, a = a * a % MOD) 
        if (b & 1) res = res * a % MOD;
    return res;
}
int C(int n, int k){
    if (k > n) return 0;
    return (1ll * fact[n] * inv_fact[k] % MOD) * inv_fact[n - k] % MOD;
}
void main(void) {
    fact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = fact[i - 1] * i % MOD;
    inv_fact[N - 1] = binpow(fact[N - 1], MOD - 2, MOD);
    for (int i = N - 2; i >= 0; i--)
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
}

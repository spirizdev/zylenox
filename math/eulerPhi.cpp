// co-prime number with n in the range from 1 to n
int phi(int n) {
    if (n == 0) return 0;
    int ans = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans -= ans / i;
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans -= ans / n;
    return ans;
}
void eulerPhi(int n) {
    vi phi(n + 1);
    iota(all(phi), 0);
    for (int i = 2; i <= n; i++) if (phi[i] == i) {
        for (int j = i; j <= n; j += i)
            phi[j] -= phi[j] / i;
    }
}

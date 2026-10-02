const int BASE_DIGITS = 9;
const int BASE = 1000000000;
struct BigInt {
    int sign;
    vi a;
    BigInt() : sign(1) {}
    BigInt(ll v) {
        *this = v;
    }
    BigInt& operator = (ll v) {
        sign = 1;
        if (v < 0) {
            sign = -1;
            v = -v;
        }
        a.clear();
        for (; v > 0; v = v / BASE)
            a.pb(v % BASE);
        return *this;
    }
    BigInt(const string& s) {
        read(s);
    }
    void read(const string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.pb(x);
        }
        trim();
    }
    friend istream& operator>>(istream &stream, BigInt &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }
    friend ostream& operator<<(ostream &stream, const BigInt &v) {
        if (v.sign == -1 && !v.isZero())
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(BASE_DIGITS) << setfill('0') << v.a[i];
        return stream;
    }
    bool operator<(const BigInt &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * v.sign;
        for (int i = ((int) a.size()) - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }
    bool operator>(const BigInt &v) const {
        return v < *this;
    }
    bool operator<=(const BigInt &v) const {
        return !(v < *this);
    }
    bool operator>=(const BigInt &v) const {
        return !(*this < v);
    }
    bool operator==(const BigInt &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const BigInt &v) const {
        return *this < v || v < *this;
    }
    friend int __compare_abs(const BigInt& x, const BigInt& y) {
        if (x.a.size() != y.a.size()) {
            return x.a.size() < y.a.size() ? -1 : 1;
        }
        for (int i = ((int) x.a.size()) - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) {
                return x.a[i] < y.a[i] ? -1 : 1;
            }
        }
        return 0;
    }
    BigInt operator-() const {
        BigInt res = *this;
        if (isZero()) return res;

        res.sign = -sign;
        return res;
    }
    void __internal_add(const BigInt& v) {
        if (a.size() < v.a.size()) {
            a.resize(v.a.size(), 0);
        }
        for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
            if (i == (int) a.size()) a.pb(0);
            a[i] += carry + (i < (int) v.a.size() ? v.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
    }
    void __internal_sub(const BigInt& v) {
        for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
            a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        this->trim();
    }
    BigInt operator += (const BigInt& v) {
        if (sign == v.sign) {
            __internal_add(v);
        } else {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
            }
        }
        return *this;
    }
    BigInt operator -= (const BigInt& v) {
        if (sign == v.sign) {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
                this->sign = -this->sign;
            }
        } else {
            __internal_add(v);
        }
        return *this;
    }
    template< typename L, typename R >
    typename enable_if<
    is_convertible<L, BigInt>::value &&
    is_convertible<R, BigInt>::value &&
    is_lvalue_reference<R&&>::value,
    BigInt>::type friend operator + (L&& l, R&& r) {
        BigInt result(forward<L>(l));
        result += r;
        return result;
    }
    template< typename L, typename R >
    typename enable_if<
    is_convertible<L, BigInt>::value &&
    is_convertible<R, BigInt>::value &&
    is_rvalue_reference<R&&>::value,
    BigInt>::type friend operator + (L&& l, R&& r) {
        BigInt result(move(r));
        result += l;
        return result;
    }
    template< typename L, typename R >
    typename enable_if<
    is_convertible<L, BigInt>::value &&
    is_convertible<R, BigInt>::value,
    BigInt>::type friend operator - (L&& l, R&& r) {
        BigInt result(forward<L>(l));
        result -= r;
        return result;
    }
    friend pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1) {
        assert(b1 > 0);
        ll norm = BASE / (b1.a.back() + 1);
        BigInt a = a1.abs() * norm;
        BigInt b = b1.abs() * norm;
        BigInt q = 0, r = 0;
        q.a.resize(a.a.size());
        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= BASE;
            r += a.a[i];
            ll s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            ll s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            ll d = ((ll) BASE * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0) {
                r += b, --d;
            }
            q.a[i] = d;
        }
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        auto res = make_pair(q, r / norm);
        if (res.second < 0) res.second += b1;
        return res;
    }
    BigInt operator/(const BigInt &v) const {
        if (v < 0) return divmod(-*this, -v).first;
        return divmod(*this, v).first;
    }
    BigInt operator%(const BigInt &v) const {
        return divmod(*this, v).second;
    }
    void operator/=(int v) {
        assert(v > 0);
        if (llabs(v) >= BASE) {
            *this /= BigInt(v);
            return ;
        }
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
            ll cur = a[i] + rem * (ll) BASE;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }
    BigInt operator/(int v) const {
        assert(v > 0);
        if (llabs(v) >= BASE) {
            return *this / BigInt(v);
        }
        BigInt res = *this;
        res /= v;
        return res;
    }
    void operator/=(const BigInt &v) {
        *this = *this / v;
    }
    ll operator%(ll v) const {
        assert(v > 0);
        assert(v < BASE);
        int m = 0;
        for (int i = a.size() - 1; i >= 0; --i)
            m = (a[i] + m * (ll) BASE) % v;
        return m * sign;
    }
    void operator*=(int v) {
        if (llabs(v) >= BASE) {
            *this *= BigInt(v);
            return ;
        }
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
            if (i == (int) a.size())
                a.pb(0);
            ll cur = a[i] * (ll) v + carry;
            carry = (int) (cur / BASE);
            a[i] = (int) (cur % BASE);
        }
        trim();
    }
    BigInt operator*(int v) const {
        if (llabs(v) >= BASE) {
            return *this * BigInt(v);
        }
        BigInt res = *this;
        res *= v;
        return res;
    }
    static vi convert_base(const vi &a, int old_digits, int new_digits) {
        vector<ll> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int) p.size(); i++)
            p[i] = p[i - 1] * 10;
        vi res;
        ll cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int) a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.pb((ll)(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.pb((int) cur);
        while (!res.empty() && !res.back())
            res.pop_back();
        return res;
    }
    void fft(vector<complex<double> > &x, bool invert) const {
        int n = (int) x.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j >= bit; bit >>= 1)
                j -= bit;
            j += bit;
            if (i < j)
                swap(x[i], x[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * 3.14159265358979323846 / len * (invert ? -1 : 1);
            complex<double> wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                complex<double> w(1);
                for (int j = 0; j < len / 2; ++j) {
                    complex<double> u = x[i + j];
                    complex<double> v = x[i + j + len / 2] * w;
                    x[i + j] = u + v;
                    x[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert)
            for (int i = 0; i < n; ++i)
                x[i] /= n;
    }
    void multiply_fft(const vi &x, const vi &y, vi &res) const {
        vector<complex<double>> fa(all(x));
        vector<complex<double>> fb(all(y));
        int n = 1;
        while (n < (int) max(x.size(), y.size()))
            n <<= 1;
        n <<= 1;
        fa.resize(n);
        fb.resize(n);
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; ++i)
            fa[i] *= fb[i];
        fft(fa, true);
        res.resize(n);
        ll carry = 0;
        for (int i = 0; i < n; ++i) {
            ll t = (ll) (fa[i].real() + 0.5) + carry;
            carry = t / 1000;
            res[i] = t % 1000;
        }
    }
    BigInt mul_simple(const BigInt &v) const {
        BigInt res;
        res.sign = sign * v.sign;
        res.a.resize(a.size() + v.a.size());
        for (int i = 0; i < (int) a.size(); ++i)
            if (a[i])
                for (int j = 0, carry = 0; j < (int) v.a.size() || carry; ++j) {
                    ll cur = res.a[i + j] + (ll) a[i] * (j < (int) v.a.size() ? v.a[j] : 0) + carry;
                    carry = (int) (cur / BASE);
                    res.a[i + j] = (int) (cur % BASE);
                }
        res.trim();
        return res;
    }
    typedef vector<ll> vll;
    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }
        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());
        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);
        for (int i = 0; i < k; i++)
            a2[i] += a1[i];
        for (int i = 0; i < k; i++)
            b2[i] += b1[i];
        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int) a1b1.size(); i++)
            r[i] -= a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            r[i] -= a2b2[i];
        for (int i = 0; i < (int) r.size(); i++)
            res[i + k] += r[i];
        for (int i = 0; i < (int) a1b1.size(); i++)
            res[i] += a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            res[i + n] += a2b2[i];
        return res;
    }
    BigInt mul_karatsuba(const BigInt &v) const {
        vi x6 = convert_base(this->a, BASE_DIGITS, 6);
        vi y6 = convert_base(v.a, BASE_DIGITS, 6);
        vll x(all(x6));
        vll y(all(y6));
        while (x.size() < y.size())
            x.pb(0);
        while (y.size() < x.size())
            y.pb(0);
        while (x.size() & (x.size() - 1))
            x.pb(0), y.pb(0);
        vll c = karatsubaMultiply(x, y);
        BigInt res;
        res.sign = sign * v.sign;
        ll carry = 0;
        for (int i = 0; i < (int) c.size(); i++) {
            ll cur = c[i] + carry;
            res.a.pb((int) (cur % 1000000));
            carry = cur / 1000000;
        }
        res.a = convert_base(res.a, 6, BASE_DIGITS);
        res.trim();
        return res;
    }
    void operator*=(const BigInt &v) {
        *this = *this * v;
    }
    BigInt operator*(const BigInt &v) const {
        if (a.size() * v.a.size() <= 1000111) return mul_simple(v);
        if (a.size() > 500111 || v.a.size() > 500111) return mul_fft(v);
        return mul_karatsuba(v);
    }
    BigInt mul_fft(const BigInt& v) const {
        BigInt res;
        res.sign = sign * v.sign;
        multiply_fft(convert_base(a, BASE_DIGITS, 3), convert_base(v.a, BASE_DIGITS, 3), res.a);
        res.a = convert_base(res.a, 3, BASE_DIGITS);
        res.trim();
        return res;
    }
    BigInt abs() const {
        BigInt res = *this;
        res.sign *= res.sign;
        return res;
    }
    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }
    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }
    friend BigInt gcd(const BigInt &a, const BigInt &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    friend BigInt lcm(const BigInt &a, const BigInt &b) {
        return a / gcd(a, b) * b;
    }
    friend BigInt sqrt(const BigInt &a1) {
        BigInt a = a1;
        while (a.a.empty() || a.a.size() % 2 == 1)
            a.a.pb(0);
        int n = a.a.size();
        int firstDigit = (int) sqrt((double) a.a[n - 1] * BASE + a.a[n - 2]);
        int norm = BASE / (firstDigit + 1);
        a *= norm;
        a *= norm;
        while (a.a.empty() || a.a.size() % 2 == 1)
            a.a.pb(0);
        BigInt r = (ll) a.a[n - 1] * BASE + a.a[n - 2];
        firstDigit = (int) sqrt((double) a.a[n - 1] * BASE + a.a[n - 2]);
        int q = firstDigit;
        BigInt res;
        for(int j = n / 2 - 1; j >= 0; j--) {
            for(; ; --q) {
                BigInt r1 = (r - (res * 2 * BigInt(BASE) + q) * q) * BigInt(BASE) * BigInt(BASE) + (j > 0 ? (ll) a.a[2 * j - 1] * BASE + a.a[2 * j - 2] : 0);
                if (r1 >= 0) {
                    r = r1;
                    break;
                }
            }
            res *= BASE;
            res += q;
            if (j > 0) {
                int d1 = res.a.size() + 2 < r.a.size() ? r.a[res.a.size() + 2] : 0;
                int d2 = res.a.size() + 1 < r.a.size() ? r.a[res.a.size() + 1] : 0;
                int d3 = res.a.size() < r.a.size() ? r.a[res.a.size()] : 0;
                q = ((ll) d1 * BASE * BASE + (ll) d2 * BASE + d3) / (firstDigit * 2);
            }
        }
        res.trim();
        return res / norm;
    }
};

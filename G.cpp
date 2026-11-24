#include <bits/stdc++.h>
using namespace std;
using u32 = unsigned;
using i64 = long long;
using i128 = __int128;

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
    explicit lazy_segtree(int n) : lazy_segtree(vector<S>(n, e())) {}
    explicit lazy_segtree(const vector<S> &v) : _n(int(v.size())) {
        size = 1 << (__lg(max(1, _n - 1)) + 1);
        log = __builtin_ctz((u32)size);
        d = vector<S>(2 * size, e());
        lz = vector<F>(size, id());
        for (auto i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (auto i = size - 1; 1 <= i; i--) {
            update(i);
        }
    }
    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (auto i = log; i >= 1; i--)
            push(p >> i);
        d[p] = x;
        for (auto i = 1; i <= log; i++)
            update(p >> i);
    }
    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (auto i = log; i >= 1; i--)
            push(p >> i);
        return d[p];
    }
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return e();
        l += size;
        r += size;
        for (auto i = log; i >= 1; i--) {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1)
                sml = op(sml, d[l++]);
            if (r & 1)
                smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    S all_prod() { return d[1]; }
    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (auto i = log; i >= 1; i--)
            push(p >> i);
        d[p] = mapping(f, d[p]);
        for (auto i = 1; i <= log; i++)
            update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return;
        l += size;
        r += size;
        for (auto i = log; i >= 1; i--) {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }
        {
            auto l2 = l, r2 = r;
            while (l < r) {
                if (l & 1)
                    all_apply(l++, f);
                if (r & 1)
                    all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (auto i = 1; i <= log; i++) {
            if (((l >> i) << i) != l)
                update(l >> i);
            if (((r >> i) << i) != r)
                update((r - 1) >> i);
        }
    }
    int _n, size, log;
    vector<S> d;
    vector<F> lz;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size)
            lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

constexpr auto inf = numeric_limits<int>::max() / 2;
int op(int a, int b) { return max(a, b); }
int e() { return -inf; }
int mapping(int f, int x) { return x + f; };
int composition(int f, int g) { return f + g; }
int id() { return 0; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string S;
    cin >> S;
    vector<int> A;
    A.push_back(1);
    for (auto x : S) {
        A.push_back(x == '(' ? 0 : 1);
    }
    auto N = int(A.size());
    vector<int> pref(N);
    for (auto i = 1; i < N; ++i) {
        pref[i] = A[i - 1] == 0 && A[i] == 1;
    }
    for (auto i = 1; i < N; ++i) {
        pref[i] += pref[i - 1];
    }
    vector<int> suff(N + 1);
    for (auto i = 0; i < N - 1; ++i) {
        suff[i] = A[i] == 0 && A[i + 1] == 1;
    }
    for (auto i = N - 1; 0 < i; --i) {
        suff[i - 1] += suff[i];
    }
    using T = lazy_segtree<int, op, e, int, mapping, composition, id>;
    vector<T> seg(4, T(N));
    for (auto i = 0; i < N - 1; ++i) {
        if (A[i] == 0 && A[i + 1] == 0) {
            seg[0].set(i, pref[i]);
        } else if (A[i] == 0 && A[i + 1] == 1) {
            seg[1].set(i, pref[i]);
        } else if (A[i] == 1 && A[i + 1] == 0) {
            seg[2].set(i, pref[i]);
        } else {
            seg[3].set(i, pref[i]);
        }
    }
    auto ans = pref[N - 1]; // no flip
    // flip once
    for (auto i = 2; i < N; ++i) {
        if (A[i - 1] == 1 && A[i] == 0) {
            seg[0].apply(0, i - 1, 1);
            seg[1].apply(0, i - 1, 1);
            seg[2].apply(0, i - 1, 1);
            seg[3].apply(0, i - 1, 1);
        }
        array<int, 4> W{};
        if (A[i] == 1) {
            W[0b00] += 1;
            W[0b01] += 1;
        }
        if (i + 1 < N && A[i + 1] == 1) {
            W[0b00] += 1;
            W[0b10] += 1;
        }
        auto val = 0;
        for (auto j = 0; j < 4; ++j) {
            val = max(val, seg[j].prod(0, i - 1) + W[j]);
        }
        val += suff[i + 1];
        ans = max(ans, val);
    }
    cout << ans << "\n";
}

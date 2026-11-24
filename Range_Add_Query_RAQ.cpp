#include <bits/stdc++.h>
using namespace std;

template <typename S, typename F, auto mapping, auto composition, auto id> struct commutative_dual_segtree {
    commutative_dual_segtree(const vector<S> &a) : n(a.size()), m(bit_ceil(a.size())), data(a), lazy(m, id()) {}
    S get(int i) {
        assert(0 <= i && i < n);
        S res = data[i];
        for (i = (i + m) >> 1; i; i >>= 1)
            res = mapping(lazy[i], res);
        return res;
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n);
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply_(l++, f);
            if (r & 1) apply_(--r, f);
        }
    }
    void apply_(int k, F f) {
        if (k < m) lazy[k] = composition(f, lazy[k]);
        else       data[k - m] = mapping(f, data[k - m]);
    }
    int n, m;
    vector<S> data;
    vector<F> lazy;
};

using S = int;
using F = int;
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    commutative_dual_segtree<S, F, mapping, composition, id> seg(vector<S>(N, 0));
    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            seg.apply(l, r, x);
        } else {
            int i;
            cin >> i;
            --i;
            cout << seg.get(i) << "\n";
        }
    }
}

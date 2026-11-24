#include <atcoder/fenwicktree>
#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

vector<int> euler_phi(int n) {
    assert(n > 0);
    vector<int> prime, phi(n + 1);
    vector<char> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    phi[1] = 1;
    for (auto i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : prime) {
            if (i * p > n) {
                break;
            }
            is_prime[i * p] = false;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }
    return phi;
}

auto phi = euler_phi(5'000'000);
int depth[5'000'001];

int e() { return -1; }

int op(int a, int b) {
    if (a == e())
        return b;
    if (b == e())
        return a;
    while (a != b) {
        if (a < b) {
            b = phi[b];
        } else {
            a = phi[a];
        }
    }
    return a;
}

struct DSU {
    explicit DSU(int n) : parent_or_size(n, -1), idx(n) { ranges::iota(idx, 0); }
    int leader(int a) { return parent_or_size[a] < 0 ? a : parent_or_size[a] = leader(parent_or_size[a]); }
    void merge(int a, int b) {
        a = leader(a);
        b = leader(b);
        if (a == b)
            return;
        if (-parent_or_size[a] < -parent_or_size[b])
            swap(a, b);
        parent_or_size[a] += parent_or_size[b];
        parent_or_size[b] = a;
        idx[a] = max(idx[a], idx[b]);
    }
    int max_idx(int a) { return idx[leader(a)]; }
    vector<int> parent_or_size, idx;
};

void solve() {
    depth[1] = 0;
    for (auto i = 1; i <= 5'000'000; ++i) {
        depth[i] = depth[phi[i]] + 1;
    }
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    read(A);
    atcoder::segtree<int, op, e> seg(A);
    DSU dsu(N);
    atcoder::fenwick_tree<int> ft(N);
    for (auto i = 0; i < N; ++i) {
        ft.add(i, depth[A[i]]);
    }
    auto update = [&](int l, int r) {
        for (auto i = l; i < r; i = dsu.max_idx(i) + 1) {
            auto x = seg.get(i);
            seg.set(i, phi[x]);
            ft.add(i, depth[phi[x]] - ft.sum(i, i + 1));
            if (0 < i && phi[x] == 1) {
                dsu.merge(i - 1, i);
            }
        }
    };
    auto query = [&](int l, int r) {
        auto lca = seg.prod(l, r);
        return ft.sum(l, r) - depth[lca] * (r - l);
    };
    while (Q--) {
        int t, l, r;
        cin >> t >> l >> r;
        --l;
        if (t == 1) {
            update(l, r);
        } else {
            cout << query(l, r) << "\n";
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}

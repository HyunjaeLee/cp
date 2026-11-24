#include <atcoder/fenwicktree>
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

struct DSU {
    explicit DSU(int n) : p(n, -1), l(n), r(n) {
        ranges::iota(l, 0);
        ranges::iota(r, 0);
    }
    int leader(int a) { return p[a] < 0 ? a : p[a] = leader(p[a]); }
    void merge(int a, int b) {
        a = leader(a);
        b = leader(b);
        assert(a != b);
        if (-p[a] < -p[b])
            swap(a, b);
        p[a] += p[b];
        p[b] = a;
        l[a] = min(l[a], l[b]);
        r[a] = max(r[a], r[b]);
    }
    int size(int a) { return -p[leader(a)]; }
    vector<int> p, l, r;
};

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    auto X = ranges::max(A);
    atcoder::fenwick_tree<int> f(N), f0(N), f1(N);
    for (auto i = 0; i < N; ++i) {
        if (A[i] == X) {
            f.add(i, 1);
        }
    }
    for (auto i = 0; i < N; i += 2) {
        if (A[i] == X) {
            f0.add(i, 1);
        }
    }
    for (auto i = 1; i < N; i += 2) {
        if (A[i] == X) {
            f1.add(i, 1);
        }
    }
    vector<int> color(N);
    DSU dsu(N);
    auto good = 0;
    auto ans = 0, sum = 0;
    auto Nice = [&](int i) {
        auto s = dsu.size(i);
        auto x = dsu.leader(i);
        auto l = dsu.l[x];
        auto r = dsu.r[x];
        if ((s & 1) && (l & 1) == 0) {
            return f0.sum(l, r + 1);
        } else if ((s & 1) && (l & 1)) {
            return f1.sum(l, r + 1);
        } else {
            return f.sum(l, r + 1);
        }
    };
    auto Erase = [&](int i) {
        sum -= ceil_div(dsu.size(i), 2);
        if (Nice(i)) {
            good--;
        }
    };
    auto Update = [&](int i, int j) {
        if (i < 0 || N <= i || j < 0 || N <= j)
            return;
        if (color[i] == 0 || color[j] == 0)
            return;
        if (dsu.leader(i) == dsu.leader(j))
            return;
        Erase(i);
        Erase(j);
        dsu.merge(i, j);
        sum += ceil_div(dsu.size(i), 2);
        if (Nice(i)) {
            good++;
        }
    };
    vector<int> I(N);
    ranges::iota(I, 0);
    ranges::sort(I, {}, [&](int i) { return -A[i]; });
    for (auto i : I) {
        color[i] = 1;
        sum++;
        if (Nice(i)) {
            good++;
        }
        Update(i, i - 1);
        Update(i, i + 1);
        auto penalty = int(good == 0);
        ans = max(ans, X + sum + A[i] - penalty);
    }
    cout << ans << "\n";
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

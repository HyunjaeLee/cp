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

#pragma GCC optimize("O3,unroll-loops")
#ifdef __x86_64__
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif

template <typename T, int N> struct simd_segtree {
    static constexpr int cache_size = 64;
    static constexpr int reg_size = 32;
    static constexpr int reg_count = cache_size / reg_size;
    static constexpr int branching = cache_size / sizeof(T);
    static constexpr int branching_bits = std::__lg(branching);
    typedef T __attribute__((vector_size(reg_size))) vec;
    struct Precalc {
        alignas(cache_size) T mask[branching][branching];
        constexpr Precalc() : mask{} {
            for (int i = 0; i < branching; ++i)
                for (int j = 0; j < branching; ++j)
                    mask[i][j] = (i < j ? -1 : 0);
        }
    };
    static constexpr Precalc precalc{};
    static constexpr int calc_height(int n) { return (n <= branching ? 1 : calc_height(n / branching) + 1); }
    static constexpr int calc_offset(int h) {
        int s = 0, n = N;
        while (h--) {
            n = (n + branching - 1) / branching;
            s += n * branching + branching;
        }
        return s;
    }
    static constexpr int round(int k) { return k & ~(branching - 1); }
    static constexpr int H = calc_height(N);
    template <std::size_t... indices>
    static constexpr std::array<int, H + 1> calc_offsets(std::index_sequence<indices...>) {
        return {calc_offset(indices)...};
    }
    static constexpr auto offset = calc_offsets(std::make_index_sequence<H + 1>());
    alignas(cache_size) T values[offset[H]]{};
    void add(int k, T x) {
        vec v = x + vec{};
        for (int h = 0; h != H; ++h) {
            auto a = (vec *)&values[offset[h] + round(k)];
            const auto m = (const vec *)&precalc.mask[k % branching];
            for (int i = 0; i != reg_count; ++i)
                a[i] += v & m[i];
            k >>= branching_bits;
        }
    }
    T sum(int i) {
        T s = 0;
        for (int h = 0; h != H; ++h) {
            s += values[offset[h] + i];
            i >>= branching_bits;
        }
        return s;
    }
    T sum(int i, int j) {
        T s = 0;
        for (int h = 0; h != H; ++h) {
            s -= values[offset[h] + i];
            s += values[offset[h] + j];
            i >>= branching_bits;
            j >>= branching_bits;
        }
        return s;
    }
};

i64 count_inversions(const vector<int> &a) {
    auto n = int(a.size());
    simd_segtree<int, 100100> seg;
    i64 cnt = 0;
    for (auto i = n - 1; 0 <= i; --i) {
        cnt += seg.sum(0, a[i]);
        seg.add(a[i], 1);
    }
    return cnt;
}

void solve() {
    int N, K, Q;
    cin >> N >> K >> Q;
    vector<int> A(N);
    read<1>(A);
    vector<vector<int>> F(K);
    for (auto i = 0; i < N; ++i) {
        F[A[i]].push_back(i);
    }
    vector<int> P(N);
    ranges::iota(P, 0);
    vector<pair<int, int>> qs(Q);
    for (auto i = 0; i < Q; ++i) {
        int j;
        cin >> j;
        qs[i] = {P[j - 1], P[j]};
        swap(P[j - 1], P[j]);
    }
    vector<vector<int>> G(K);
    for (auto [x, y] : qs) {
        if (size(F[x]) < size(F[y])) {
            G[y].push_back(x);
        } else {
            G[x].push_back(y);
        }
    }
    simd_segtree<int, 100100> seg;
    map<pair<int, int>, i64> mp;
    for (auto x = 0; x < K; ++x) {
        ranges::sort(G[x]);
        auto r = ranges::unique(G[x]);
        G[x].erase(r.begin(), r.end());
        for (auto i : F[x]) {
            seg.add(i, 1);
        }
        for (auto y : G[x]) {
            i64 cnt = 0;
            for (auto i : F[y]) {
                cnt += seg.sum(i + 1, N);
            }
            mp[{x, y}] = cnt;
        }
        for (auto i : F[x]) {
            seg.add(i, -1);
        }
    }
    auto ans = count_inversions(A);
    for (auto [x, y] : qs) {
        i64 delta = 0;
        if (mp.contains({x, y})) {
            auto xy = mp[{x, y}];
            auto yx = ssize(F[x]) * ssize(F[y]) - xy;
            delta = yx - xy;
        } else {
            auto yx = mp[{y, x}];
            auto xy = ssize(F[x]) * ssize(F[y]) - yx;
            delta = yx - xy;
        }
        ans += delta;
        cout << ans << "\n";
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

#include <atcoder/dsu>
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

i64 F(const vector<int> &a, int K) {
    auto n = int(a.size());
    auto H = ranges::max(a);
    vector<vector<int>> G(H + 1);
    for (auto i = 0; i < n; ++i) {
        G[a[i]].push_back(i);
    }
    atcoder::dsu dsu(n);
    vector<int> color(n);
    i64 sum = 0;
    atcoder::fenwick_tree<i64> f0(n + 1), f1(n + 1), f2(n + 1);
    auto Update = [&](int i, int s) {
        auto w = dsu.size(i);
        f0.add(w, s * 1);
        f1.add(w, s * w);
        f2.add(w, s * i64(w) * w);
    };
    for (auto h = H; 0 < h; --h) {
        for (auto i : G[h]) {
            color[i] = 1;
            if (0 <= i - 1 && color[i - 1]) {
                Update(i - 1, -1);
                dsu.merge(i - 1, i);
            }
            if (i + 1 < n && color[i + 1]) {
                Update(i + 1, -1);
                dsu.merge(i, i + 1);
            }
            Update(i, 1);
        }
        auto l = K / h;
        sum += (f2.sum(0, min(l, n + 1)) + f1.sum(0, min(l, n + 1))) / 2 +
               i64(l) * (l + 1) / 2 * f0.sum(min(l, n + 1), n + 1) + l * f1.sum(min(l, n + 1), n + 1) -
               i64(l) * l * f0.sum(min(l, n + 1), n + 1);
    }
    return sum;
}

auto transpose(const vector<vector<int>> &A) {
    auto N = int(A.size());
    auto M = int(A[0].size());
    vector<vector<int>> B(M, vector<int>(N));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            B[j][i] = A[i][j];
        }
    }
    return B;
}

void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> A(N, vector<int>(M));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            char c;
            cin >> c;
            if (c == '.') {
                A[i][j] = 1;
            }
        }
    }
    if (N > M) {
        A = transpose(A);
        swap(N, M);
    }
    vector<int> v(M);
    i64 ans = 0;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (A[i][j]) {
                v[j]++;
            } else {
                v[j] = 0;
            }
        }
        ans += F(v, K);
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

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

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<i64> A(N);
    read(A);
    vector<i64> P(N + 1);
    for (auto i = 1; i <= N; ++i) {
        P[i] = A[i - 1] + P[i - 1];
    }
    vector<vector<pair<i64, i64>>> tree(4 * N);
    auto cross = [](pair<i64, i64> a, pair<i64, i64> b) {
        auto [x1, y1] = a;
        auto [x2, y2] = b;
        return i128(x1) * y2 - i128(y1) * x2;
    };
    auto merge = [&](vector<pair<i64, i64>> a, vector<pair<i64, i64>> b) {
        for (auto [x, y] : b) {
            while (2 <= a.size()) {
                auto [x1, y1] = a[int(a.size()) - 2];
                auto [x2, y2] = a[int(a.size()) - 1];
                if (0 < cross({x2 - x1, y2 - y1}, {x - x1, y - y1})) {
                    break;
                } else {
                    a.pop_back();
                }
            }
            a.emplace_back(x, y);
        };
        return a;
    };
    [&](this auto &&self, int u, int ul, int ur) -> void {
        if (ur - ul == 1) {
            tree[u].emplace_back(ul, P[ul]);
            return;
        }
        auto mid = (ul + ur) / 2;
        self(2 * u, ul, mid);
        self(2 * u + 1, mid, ur);
        tree[u] = merge(tree[2 * u], tree[2 * u + 1]);
    }(1, 1, N + 1);
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    auto query = [&](this auto &&self, int l, int r, int u, int ul, int ur) -> i64 {
        if (ur <= l || r <= ul) {
            return inf;
        }
        if (l <= ul && ur <= r) {
            auto k = int(tree[u].size());
            auto f = [&](int i) {
                auto [x, y] = tree[u][i];
                return (long double)(y - P[l - 1]) / (long double)(x - (l - 1));
            };
            auto pred = [&](int i) { return f(i) > f(i + 1); };
            auto it = ranges::partition_point(views::iota(0, k - 1), pred);
            auto [x, y] = tree[u][*it];
            return floor_div(y - P[l - 1], x - (l - 1));
        }
        auto mid = (ul + ur) / 2;
        return min(self(l, r, 2 * u, ul, mid), self(l, r, 2 * u + 1, mid, ur));
    };
    while (Q--) {
        int l, k;
        cin >> l >> k;
        auto r = l + k;
        auto ans = query(l, r, 1, 1, N + 1);
        if (ans < 0) {
            cout << "stay with parents\n";
        } else {
            cout << ans << "\n";
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

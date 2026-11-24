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

#define TC
void solve() {
    i64 N, M;
    cin >> N >> M;
    vector<array<i64, 2>> A(N);
    vector<i64> X;
    for (auto &[x, p] : A) {
        cin >> x >> p;
        X.push_back(x);
        X.push_back(x - p);
        X.push_back(x + p);
    }
    ranges::sort(X);
    X.erase(unique(X.begin(), X.end()), X.end());
    vector<i64> G(size(X));
    auto xtoi = [&](i64 x) {
        auto it = ranges::lower_bound(X, x);
        assert(it != X.end() && *it == x);
        return it - X.begin();
    };
    for (auto &[x, p] : A) {
        G[xtoi(x - p)] += 1;
        G[xtoi(x)] -= 2;
        G[xtoi(x + p)] += 1;
    }
    i64 slope = 0;
    vector<i64> Y(size(X));
    for (auto i = 1; i < ssize(X); ++i) {
        slope += G[i - 1];
        auto dx = X[i] - X[i - 1];
        Y[i] = Y[i - 1] + slope * dx;
    }
    vector<array<i64, 2>> B;
    for (auto i = 0; i < ssize(X); ++i) {
        if (M < Y[i]) {
            B.push_back({X[i], Y[i] - M});
        }
    }
    for (auto &[x, y] : A) {
        tie(x, y) = pair{x + y, -x + y};
    }
    for (auto &[x, y] : B) {
        tie(x, y) = pair{x + y, -x + y};
    }
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    auto max_x = -inf, max_y = -inf;
    for (auto [x, y] : B) {
        max_x = max(max_x, x);
        max_y = max(max_y, y);
    }
    for (auto [x, y] : A) {
        cout << (max_x <= x && max_y <= y ? 1 : 0);
    }
    cout << "\n";
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

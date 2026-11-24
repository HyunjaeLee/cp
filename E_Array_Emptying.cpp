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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    read(A);
    auto pred = [&](int e) {
        priority_queue<int> X(begin(A), end(A));
        priority_queue<int> Y;
        for (auto i = K + e; i < K + 2 * e + N; ++i) {
            Y.push(i);
        }
        while (!X.empty()) {
            auto x = X.top();
            X.pop();
            auto y = Y.top();
            Y.pop();
            if (x <= y)
                continue;
            if (e-- == 0) {
                return 1;
            }
            X.push(ceil_div(x, 2));
            X.push(ceil_div(x, 2));
            Y.push(y);
        }
        return 0;
    };
    auto it = ranges::partition_point(views::iota(0, 3 * N), pred);
    auto e = *it;
    auto ans = N + 2 * e;
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

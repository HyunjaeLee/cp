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
    int N;
    if (!(cin >> N)) {
        exit(0);
    }
    vector<array<i64, 2>> A(N);
    for (auto &[x, y] : A) {
        cin >> x >> y;
    }
    if (N < 3) {
        cout << N << "\n";
        return;
    }
    mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
    for (auto t = 0; t < 30; ++t) {
        auto p = uniform_int_distribution<>(0, N - 2)(g);
        auto q = uniform_int_distribution<>(p + 1, N - 1)(g);
        auto a = A[q][0] - A[p][0];
        auto b = A[q][1] - A[p][1];
        auto cnt = 0;
        for (auto [x, y] : A) {
            x -= A[p][0];
            y -= A[p][1];
            if (a * y != b * x) {
                cnt++;
            }
        }
        if (cnt < N / 3) {
            cout << N - cnt * 3 << "\n";
            return;
        }
    }
    cout << N - (N / 3) * 3 << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (;;) {
        solve();
    }
}

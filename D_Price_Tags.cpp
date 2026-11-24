#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    i64 N, Y;
    cin >> N >> Y;
    vector<i64> A(N);
    read(A);
    auto MX = ranges::max(A);
    vector<i64> F(MX + 100);
    for (auto i = 0; i < N; ++i) {
        F[A[i]] += 1;
    }
    for (auto i = 1; i < MX + 100; ++i) {
        F[i] += F[i - 1];
    }
    auto ans = numeric_limits<i64>::min();
    for (i64 x = 2; x <= MX + 10; ++x) {
        i64 sum = 0LL;
        for (i64 i = 1; x * (i - 1) <= MX; ++i) {
            auto me = F[i] - F[i - 1];
            sum += (F[min<i64>(MX, x * i)] - F[x * (i - 1)]) * i;
            sum -= max(0LL, (F[min<i64>(MX, x * i)] - F[x * (i - 1)]) - me) * Y;
        }
        ans = max(ans, sum);
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

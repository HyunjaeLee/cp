#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

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
    cin >> N;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    for (auto i = 0; i < N - 1; ++i) {
        A[i + 1] ^= A[i];
    }
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto ans = inf;
    { // solve for odd partitions
        auto X = A[N - 1];
        auto want = X;
        auto cnt = 0;
        for (auto i = 0; i < N; ++i) {
            if (A[i] == want) {
                want ^= X;
                cnt++;
            }
        }
        ans = min(ans, N - cnt);
    }
    if (A[N - 1] == 0) { // solve for even partitions
        map<int, vector<int>> mp;
        for (auto i = 0; i < N; ++i) {
            mp[A[i]].push_back(i);
        }
        const auto &v0 = mp[0];
        for (const auto &[x, v] : mp) {
            if (x == 0) {
                ans = min(ans, N - int(size(v)));
                continue;
            }
            auto cnt = 0;
            auto last = -1;
            for (auto i : v) {
                if (i <= last)
                    continue;
                auto it = ranges::upper_bound(v0, i);
                if (it != v0.end()) {
                    cnt += 2;
                    last = *it;
                }
            }
            ans = min(ans, N - cnt);
        }
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

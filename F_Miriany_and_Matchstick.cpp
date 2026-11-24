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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        char c;
        cin >> c;
        A[i] = c - 'A';
    }
    vector<vector<vector<pair<int, int>>>> dp(N + 1, vector<vector<pair<int, int>>>(2));
    {
        auto cnt = 0;
        for (auto i = 0; i < N - 1; ++i) {
            if (A[i] != A[i + 1]) {
                cnt += 1;
            }
        }
        dp[N][0].emplace_back(cnt, cnt + 1);
        dp[N][1].emplace_back(cnt, cnt + 1);
    }
    for (auto i = N - 1; 1 <= i; --i) {
        for (auto prv : {0, 1}) {
            for (auto x : {0, 1}) {
                auto cnt = 0;
                if (prv != x)
                    cnt += 1;
                if (A[i] != x)
                    cnt += 1;
                for (auto [l, r] : dp[i + 1][x]) {
                    dp[i][prv].emplace_back(l + cnt, r + cnt);
                }
            }
            ranges::sort(dp[i][prv]);
            vector<pair<int, int>> rng;
            for (auto [l, r] : dp[i][prv]) {
                if (rng.empty() || rng.back().second < l) {
                    rng.emplace_back(l, r);
                } else {
                    rng.back().second = max(rng.back().second, r);
                }
            }
            swap(dp[i][prv], rng);
        }
    }
    auto Contains = [&](const vector<pair<int, int>> &v, int d) {
        for (auto [l, r] : v) {
            if (l + d <= K && K < r + d)
                return true;
        }
        return false;
    };
    vector<int> B(N);
    if (Contains(dp[1][0], A[0] != 0)) {
        B[0] = 0;
        K -= (A[0] != 0);
    } else if (Contains(dp[1][1], A[0] != 1)) {
        B[0] = 1;
        K -= (A[0] != 1);
    } else {
        cout << "NO\n";
        return;
    }
    for (auto i = 1; i < N; ++i) {
        for (auto x : {0, 1}) {
            auto cnt = 0;
            if (B[i - 1] != x)
                cnt += 1;
            if (A[i] != x)
                cnt += 1;
            if (Contains(dp[i + 1][x], cnt)) {
                B[i] = x;
                K -= cnt;
                break;
            }
        }
    }
    cout << "YES\n";
    for (auto i = 0; i < N; ++i) {
        cout << char('A' + B[i]);
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

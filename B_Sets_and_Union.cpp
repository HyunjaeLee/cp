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
    int N;
    cin >> N;
    vector<vector<int>> A(N);
    vector<vector<int>> F(51);
    vector<int> freq(51);
    auto cnt = 0;
    for (auto i = 0; i < N; ++i) {
        int k;
        cin >> k;
        for (auto j = 0; j < k; ++j) {
            int x;
            cin >> x;
            A[i].push_back(x);
            F[x].push_back(i);
            if (freq[x]++ == 0) {
                cnt++;
            }
        }
    }
    auto ans = 0;
    const auto C = cnt;
    for (auto x = 1; x <= 50; ++x) {
        for (auto i : F[x]) {
            for (auto j = 0; j < int(A[i].size()); ++j) {
                if (--freq[A[i][j]] == 0) {
                    cnt--;
                }
            }
        }
        if (cnt != C) {
            ans = max(ans, cnt);
        }
        for (auto i : F[x]) {
            for (auto j = 0; j < int(A[i].size()); ++j) {
                if (freq[A[i][j]]++ == 0) {
                    cnt++;
                }
            }
        }
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

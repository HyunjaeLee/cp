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
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    if (A[N - 1] == 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<pair<int, int>> rng;
    {
        auto l = 0, r = 0;
        while (r < N) {
            if (A[r] == 0) {
                ++r;
                rng.emplace_back(l, r);
                l = r;
            } else {
                ++r;
            }
        }
    }
    vector<int> ans;
    for (auto [l, r] : rng | views::reverse) {
        for (auto i = l; i < r - 1; ++i) {
            ans.push_back(0);
        }
        ans.push_back(r - l - 1);
    }
    show(ans);
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

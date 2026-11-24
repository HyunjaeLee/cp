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
    auto S = views::iota(1, N + 1) | ranges::to<set<int>>();
    for (auto i = 0; i < N; ++i) {
        if (auto it = S.find(A[i]); it != S.end()) {
            S.erase(it);
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (A[i] == 0) {
            auto it = prev(S.end());
            A[i] = *it;
            S.erase(it);
        }
    }
    vector<bool> color(N);
    for (auto i = 0; i < N; ++i) {
        if (A[i] == i + 1) {
            color[i] = true;
        } else {
            break;
        }
    }
    for (auto i = N - 1; 0 <= i; --i) {
        if (color[i])
            break;
        if (A[i] == i + 1) {
            color[i] = true;
        } else {
            break;
        }
    }
    auto ans = ranges::count(color, false);
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

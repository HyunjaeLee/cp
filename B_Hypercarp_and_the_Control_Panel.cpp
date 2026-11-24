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
    vector B{pair{A[0], 1}};
    for (auto i = 1; i < N; ++i) {
        if (A[i - 1] == A[i]) {
            B.back().second += 1;
        } else {
            B.push_back({A[i], 1});
        }
    }
    auto ex = 0;
    for (auto i = 0; i < int(B.size()); ++i) {
        if (B[i].second == 1) {
            if (i == 0) {
                if (i + 1 < int(B.size()) && B[i + 1].second >= 2) {
                    ex = 1;
                }
            } else if (i == int(B.size()) - 1) {
                if (B[i - 1].second >= 2) {
                    ex = 1;
                }
            } else {
                if ((B[i - 1].second >= 2 || B[i + 1].second >= 2) && B[i - 1].first != B[i + 1].first) {
                    ex = 1;
                }
            }
        }
    }
    for (auto [x, y] : views::pairwise(B)) {
        if (x.second >= 2 && y.second >= 2) {
            ex = 2;
        }
    }
    auto ans = int(B.size()) + ex;
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

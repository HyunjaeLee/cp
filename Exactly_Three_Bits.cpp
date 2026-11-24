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
    i64 N;
    cin >> N;
    vector<int> P;
    for (auto i = 59; 0 <= i; --i) {
        if ((N >> i) & 1) {
            P.push_back(i);
        }
    }
    i64 ans = 0;
    if (3 <= size(P)) {
        ans = (1LL << P[0]) | (1LL << P[1]) | (1LL << P[2]);
    } else if (2 == size(P)) {
        if (2 <= P[1]) {
            ans = (1LL << P[0]) | (1LL << (P[1] - 1)) | (1LL << (P[1] - 2));
        } else {
            auto cnt = 0;
            for (auto i = P[0] - 1; 0 <= i; --i) {
                if (cnt == 3) break;
                cnt += 1;
                ans |= 1LL << i;
            }
            if (cnt < 3) {
                ans = -1;
            }
        }
    } else if (1 == size(P)) {
        if (P[0] - 3 < 0) {
            ans = -1;
        } else {
            ans = (1LL << (P[0] - 1)) | (1LL << (P[0] - 2)) | (1LL << (P[0] - 3));
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

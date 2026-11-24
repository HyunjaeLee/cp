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
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

#define TC
void solve() {
    int A, B, C;
    i64 K;
    cin >> A >> B >> C >> K;
    vector<int> P(7);
    P[0] = 1;
    for (auto i = 1; i <= 6; ++i) {
        P[i] = P[i - 1] * 10;
    }
    if (max(A, B) + 1 == C) {
        i64 cnt = 0;
        for (auto x = P[A - 1]; x < P[A]; ++x) {
            auto val = max(0, P[B] - max(P[B - 1], P[C - 1] - x));
            if (K <= cnt + val) {
                auto y = max(P[B - 1], P[C - 1] - x) + K - cnt - 1;
                auto z = x + y;
                println("{} + {} = {}", x, y, z);
                return;
            }
            cnt += val;
        }
    } else if (max(A, B) == C) {
        i64 cnt = 0;
        for (auto x = P[A - 1]; x < P[A]; ++x) {
            auto val = max(P[B - 1], min(P[B], P[C] - x)) - P[B - 1];
            if (K <= cnt + val) {
                auto y = P[B - 1] + K - cnt - 1;
                auto z = x + y;
                println("{} + {} = {}", x, y, z);
                return;
            }
            cnt += val;
        }
    }
    println("-1");
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

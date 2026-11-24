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
    cin >> N;
    string S, T;
    cin >> S >> T;
    auto l = 0, r = N - 1;
    for (; l < N; ++l) {
        if (T[l] == 'B') {
            if (S[l] != 'B') {
                cout << "-1\n";
                return;
            }
        } else {
            break;
        }
    }
    for (; 0 <= r; --r) {
        if (T[r] == 'A') {
            if (S[r] != 'A') {
                cout << "-1\n";
                return;
            }
        } else {
            r += 1;
            break;
        }
    }
    auto ans = 0;
    stack<int> st;
    for (auto i = l; i < r; ++i) {
        if (S[i] == T[i]) {
            continue;
        }
        if (T[i] == 'A') {
            st.push('(');
        } else {
            if (st.empty()) {
                ans += 1;
            } else {
                ans += 1;
                st.pop();
            }
        }
    }
    ans += int(st.size());
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

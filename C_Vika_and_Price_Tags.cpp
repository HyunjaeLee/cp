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
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    read(A);
    read(B);
    set<int> S;
    auto F = [&](this auto &&self, int x, int y, int t) -> void {
        assert(0 <= x && 0 <= y);
        if (x == 0 && y == 0) {
            return;
        }
        if (x == 0) {
            S.insert(t);
            return;
        }
        if (0 < y && 2 * y <= x) {
            auto k = x / (2 * y);
            self(x - 2 * y * k, y, t);
        } else {
            self(y, abs(x - y), (t + 1) % 3);
        }
    };
    for (auto i = 0; i < N; ++i) {
        F(A[i], B[i], 0);
    }
    cout << (S.size() <= 1 ? "YES\n" : "NO\n");
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

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
    vector<int> L(N), R(N), U(N), V(N);
    for (auto i = 0; i < N; ++i) {
        cin >> L[i] >> R[i] >> U[i] >> V[i];
    }
    vector<vector<array<int, 4>>> dp(N + 1, vector<array<int, 4>>(N + 1));
    vector<vector<bool>> vis(N + 1, vector<bool>(N + 1));
    auto f = [&](this auto &&self, int i, int cnt) -> array<int, 4> {
        if (i == N) {
            return {0, 0, 0, 0};
        }
        auto &ret = dp[i][cnt];
        if (vis[i][cnt])
            return ret;
        vis[i][cnt] = true;
        auto p = self(i + 1, cnt);
        auto a = cnt + 1;
        if (a < L[i] || R[i] < a) {
            auto q = self(i + 1, cnt + 1);
            q[1] = min(q[1], U[i] - 1);
            q[2] = max(q[2], V[i] + 1);
            p[0] = min(p[0], 1 + q[0]);
            p[1] = max(p[1], 1 + q[1]);
            p[2] = min(p[2], 1 + q[2]);
            p[3] = max(p[3], 1 + q[3]);
        }
        return ret = p;
    };
    auto p = f(0, 0);
    cout << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << "\n";
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

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

#include <atcoder/dsu>
#include <atcoder/modint>
using Z = atcoder::modint998244353;

void solve() {
    int N;
    cin >> N;
    vector<pair<int, int>> A(N);
    vector<int> P(2 * N + 1);
    for (auto &[L, R] : A) {
        cin >> L >> R;
        P[L] += 1;
        P[R] -= 1;
    }
    for (auto i = 0; i < 2 * N; ++i) {
        P[i + 1] += P[i];
    }
    for (auto i = 0; i < 2 * N + 1; ++i) {
        if (3 <= P[i]) {
            cout << "0\n";
            return;
        }
    }
    vector<vector<int>> V(2 * N + 1);
    for (auto id = 0; auto [L, R] : A) {
        for (auto i = L; i < R; ++i) {
            V[i].push_back(id);
        }
        ++id;
    }
    Z ans = Z(2).pow(N);
    atcoder::dsu dsu(N);
    for (auto i = 0; i < 2 * N + 1; ++i) {
        if (2 == V[i].size()) {
            auto u = V[i][0];
            auto v = V[i][1];
            dsu.merge(u, v);
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (dsu.leader(i) == i) {
            auto C = dsu.size(i);
            ans /= Z(2).pow(C - 1);
        }
    }
    cout << ans.val();
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

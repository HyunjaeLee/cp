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

using S = pair<int, int>;

S op(S a, S b) { return max(a, b); }

S e() { return {-1, -1}; }

#include <atcoder/segtree>

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<vector<int>> F(N);
    for (auto i = 0; i < N; ++i) {
        F[i].push_back(0);
    }
    atcoder::segtree<S, op, e> seg(Q + 1);
    seg.set(0, {0, 'a'});
    for (auto i = 1; i <= Q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            --x;
            F[x].push_back(i);
        } else {
            char c;
            cin >> c;
            seg.set(i, {i, c});
        }
    }
    string ans;
    for (auto i = 0; i < N; ++i) {
        int x = '$';
        F[i].push_back(Q + 1);
        for (auto j = 0; j + 1 < ssize(F[i]); j += 2) {
            auto l = F[i][j];
            auto r = F[i][j + 1];
            auto s = seg.prod(l, r).second;
            if (s != -1)
                x = s;
        }
        ans.push_back(char(x));
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

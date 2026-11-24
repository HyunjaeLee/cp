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
    int N, M;
    cin >> N >> M;
    vector<array<int, 4>> qs;
    for (auto i = 0; i < M; ++i) {
        char t;
        cin >> t;
        if (t == '+') {
            int u, v;
            char c;
            cin >> u >> v >> c;
            --u, --v;
            qs.push_back({t, u, v, c});
        } else if (t == '-') {
            int u, v;
            cin >> u >> v;
            --u, --v;
            qs.push_back({t, u, v});
        } else {
            int k;
            cin >> k;
            qs.push_back({t, k});
        }
    }
    vector<int> ans(M);
    {
        map<pair<int, int>, int> mp;
        auto cnt = 0;
        for (auto q = 0; q < M; ++q) {
            if (qs[q][0] == '+') {
                auto u = qs[q][1];
                auto v = qs[q][2];
                auto c = qs[q][3];
                mp[{u, v}] = c;
                if (auto it = mp.find({v, u}); it != mp.end() && it->second == c) {
                    cnt++;
                }
            } else if (qs[q][0] == '-') {
                auto u = qs[q][1];
                auto v = qs[q][2];
                auto it = mp.find({u, v});
                assert(it != mp.end());
                auto c = it->second;
                mp.erase(it);
                if (auto it1 = mp.find({v, u}); it1 != mp.end() && it1->second == c) {
                    cnt--;
                }
            } else {
                if (cnt) {
                    ans[q] = 1;
                }
            }
        }
    }
    {
        set<pair<int, int>> S;
        auto cnt = 0;
        for (auto q = 0; q < M; ++q) {
            if (qs[q][0] == '+') {
                auto u = qs[q][1];
                auto v = qs[q][2];
                S.insert({u, v});
                if (auto it = S.find({v, u}); it != S.end()) {
                    cnt++;
                }
            } else if (qs[q][0] == '-') {
                auto u = qs[q][1];
                auto v = qs[q][2];
                auto it = S.find({u, v});
                assert(it != S.end());
                S.erase(it);
                if (auto it1 = S.find({v, u}); it1 != S.end()) {
                    cnt--;
                }
            } else {
                auto k = qs[q][1];
                if (cnt && (k & 1)) {
                    ans[q] = 1;
                }
            }
        }
    }
    for (auto i = 0; i < M; ++i) {
        if (qs[i][0] == '?') {
            cout << (ans[i] ? "YES" : "NO") << "\n";
        }
    }
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

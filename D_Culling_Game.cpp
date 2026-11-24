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

#include <atcoder/fenwicktree>

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<int> P(N);
    read<1>(P);
    map<int, int> leader;
    set<int> S;
    atcoder::fenwick_tree<i64> ft(N);
    auto Insert = [&](int id) {
        ft.add(id, A[id]);
        leader[id] = id;
        auto lit = leader.find(id);
        auto [sit, _] = S.insert(id);
        auto pl = -1;
        if (lit != leader.begin()) {
            pl = prev(lit)->first;
            if (id < leader[pl]) {
                leader[id] = leader[pl];
                leader[pl] = *prev(sit);
            }
        }
        auto i = 0;
        for (auto it = pl != -1 ? leader.find(pl) : lit; next(it) != leader.end();) {
            auto l = it->first;
            auto r = it->second;
            auto sum = ft.sum(l, r + 1);
            auto nl = next(it)->first;
            if (A[nl] <= sum) { // merge
                leader[l] = leader[nl];
                leader.erase(nl);
            } else {
                if (++i == 2) {
                    return;
                }
                ++it;
            }
        }
    };
    vector<int> ans(N);
    for (auto i = N - 1; 0 <= i; --i) {
        Insert(P[i]);
        ans[i] = int(leader.size()) - 1;
    }
    show(ans);
    // vector<bool> active(N, true);
    // vector<int> ans(N);
    // for (auto i = 0; i < N; ++i) {
    //     i64 x = 0;
    //     auto cnt = -1;
    //     for (auto j = 0; j < N; ++j) {
    //         if (!active[j])
    //             continue;
    //         if (x < A[j]) {
    //             cnt++;
    //             x = A[j];
    //         } else {
    //             x += A[j];
    //         }
    //     }
    //     ans[i] = cnt;
    //     active[P[i]] = false;
    // }
    // show(ans);
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

#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>
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

constexpr auto inf = numeric_limits<i64>::max() / 2;

i64 op(i64 a, i64 b) { return min(a, b); }

i64 e() { return inf; }

i64 mapping(i64 f, i64 x) { return f + x; }

i64 composition(i64 f, i64 g) { return f + g; }

i64 id() { return 0; }

void solve() {
    int N, M, Q;
    string S;
    cin >> N >> M >> Q >> S;
    vector<pair<int, int>> rng(M);
    for (auto &[l, r] : rng) {
        cin >> l >> r;
        --l;
    }
    vector<i64> first(N, inf);
    vector<vector<pair<int, i64>>> In(N + 1);
    vector<vector<int>> Out(N + 1);
    auto T = 0LL;
    for (auto i = 0; auto [l, r] : rng) {
        In[l].emplace_back(i, T);
        Out[r].emplace_back(i);
        T += r - l;
        ++i;
    }
    atcoder::lazy_segtree<i64, op, e, i64, mapping, composition, id> seg(M);
    for (auto i = 0; i < N; ++i) {
        for (auto [rid, t] : In[i]) {
            seg.set(rid, t);
        }
        for (auto rid : Out[i]) {
            seg.set(rid, inf);
        }
        first[i] = seg.all_prod();
        seg.apply(0, M, 1);
    }
    vector<pair<i64, int>> v;
    for (auto i = 0; i < N; ++i) {
        if (first[i] < inf / 2) {
            v.emplace_back(first[i], i);
        }
    }
    ranges::sort(v);
    auto K = int(v.size());
    vector<int> mp(N, -1);
    atcoder::fenwick_tree<int> ft(K);
    for (auto i = 0; i < K; ++i) {
        assert(mp[v[i].second] == -1);
        mp[v[i].second] = i;
        ft.add(i, S[v[i].second] - '0');
    }
    auto extra = 0;
    for (auto i = 0; i < N; ++i) {
        if (mp[i] == -1) {
            extra += S[i] - '0';
        }
    }
    auto toggle = [&](int i) {
        assert(0 <= i && i < N);
        if (mp[i] == -1) {
            if (S[i] == '1') {
                S[i] = '0';
                extra--;
            } else {
                S[i] = '1';
                extra++;
            }
        } else {
            if (ft.sum(mp[i], mp[i] + 1)) {
                ft.add(mp[i], -1);
            } else {
                ft.add(mp[i], 1);
            }
        }
    };
    while (Q--) {
        int i;
        cin >> i;
        --i;
        toggle(i);
        auto sum = min(K, ft.sum(0, K) + extra);
        auto ans = sum - ft.sum(0, sum);
        cout << ans << "\n";
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
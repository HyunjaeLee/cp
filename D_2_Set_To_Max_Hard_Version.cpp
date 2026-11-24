#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

constexpr auto inf = numeric_limits<int>::max() / 2;

int op_max(int a, int b) { return max(a, b); }

int e_max() { return -inf; }

int op_min(int a, int b) { return min(a, b); }

int e_min() { return inf; }

void solve() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    vector<vector<int>> G(N + 1);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        G[A[i]].push_back(i);
    }
    for (auto i = 0; i < N; ++i) {
        cin >> B[i];
    }
    vector<pair<int, int>> P(N);
    for (auto i = 0; i < N; ++i) {
        P[i] = {B[i], i};
    }
    ranges::sort(P);
    atcoder::segtree<int, op_max, e_max> seg_max(A);
    atcoder::segtree<int, op_min, e_min> seg_min(N);
    auto probe_left = [&](int x, int pos) {
        auto it = ranges::upper_bound(G[x], pos);
        if (it == G[x].begin()) {
            return false;
        }
        --it;
        if (x < seg_max.prod(*it, pos + 1)) {
            return false;
        }
        if (seg_min.prod(*it, pos + 1) < x) {
            return false;
        }
        return true;
    };
    auto probe_right = [&](int x, int pos) {
        auto it = ranges::lower_bound(G[x], pos);
        if (it == G[x].end()) {
            return false;
        }
        if (x < seg_max.prod(pos, *it + 1)) {
            return false;
        }
        if (seg_min.prod(pos, *it + 1) < x) {
            return false;
        }
        return true;
    };
    for (auto [x, pos] : P) {
        auto ok = probe_left(x, pos) || probe_right(x, pos);
        if (!ok) {
            cout << "NO\n";
            return;
        }
        seg_min.set(pos, x);
    }
    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

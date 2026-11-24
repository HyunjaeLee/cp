#include <bits/stdc++.h>
using namespace std;
using u32 = unsigned;
using i64 = long long;
using i128 = __int128;

auto same(auto G) {
    auto W = (int)G.size();
    map<int, int> mp;
    for (auto i = 0; i < W; ++i) {
        auto sum = accumulate(begin(G[i]), end(G[i]), 0);
        mp[sum] += 1;
    }
    return mp;
}

array<i64, 20> F;

auto test(int N) {
    vector<int> A(N);
    ranges::iota(A, 1);
    auto W = bit_width(u32(N));
    vector<vector<int>> G(W, vector<int>(N));
    for (auto i = 0; i < W; ++i) {
        for (auto j = 0; j < N; ++j) {
            G[i][j] = ((A[j] >> i) & 1);
        }
    }
    return G;
}

auto koharu(vector<vector<int>> G) {
    auto proj = [](const vector<int> &v) { return pair(accumulate(begin(v), end(v), 0), v); };
    ranges::sort(G, {}, proj);
    auto W = int(G.size());
    auto N = int(G[0].size());
    vector<int> A(N);
    for (auto i = 0; i < W; ++i) {
        for (auto j = 0; j < N; ++j) {
            A[j] |= G[i][j] << i;
        }
    }
    ranges::sort(A);
    return A;
}

void solve() {
    int N;
    cin >> N;
    auto W = bit_width(u32(N));
    vector<vector<int>> G(W, vector<int>(N));
    for (auto i = 0; i < W; ++i) {
        for (auto j = 0; j < N; ++j) {
            char c;
            cin >> c;
            auto x = c - '0';
            G[i][j] = x;
        }
    }
    if (koharu(G) != koharu(test(N))) {
        cout << "0\n";
        return;
    }
    auto acc = 1LL;
    for (auto [x, cnt] : same(G)) {
        acc *= F[cnt];
    }
    cout << acc << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    F[0] = 1;
    for (auto i = 1; i < 20; ++i) {
        F[i] = F[i - 1] * i;
    }
    int t;
    cin >> t;
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}

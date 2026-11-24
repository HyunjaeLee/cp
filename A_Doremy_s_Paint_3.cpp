#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    map<int, int> G;
    for (auto i = 0; i < N; ++i) {
        G[A[i]] += 1;
    }
    auto ok = false;
    if (G.size() == 1) {
        ok = true;
    } else if (G.size() == 2) {
        for (auto [f, s] : G) {
            if (s == N / 2) {
                ok = true;
            }
        }
    } else {
        ok = false;
    }
    cout << (ok ? "Yes\n" : "No\n");
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

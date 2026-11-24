#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int a, b, xk, yk, xq, yq;
    cin >> a >> b >> xk >> yk >> xq >> yq;
    vector<pair<int, int>> v{{a, b}, {a, -b}, {-a, b}, {-a, -b}, {b, a}, {b, -a}, {-b, a}, {-b, -a}};
    set<pair<int, int>> S;
    for (auto [dxk, dyk] : v) {
        for (auto [dxq, dyq] : v) {
            auto K = pair(xk + dxk, yk + dyk);
            auto Q = pair(xq + dxq, yq + dyq);
            if (K == Q) {
                S.insert(K);
            }
        }
    }
    cout << size(S) << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

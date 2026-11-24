#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> X;
    X.push_back(0);
    for (auto i = 0; i < 30; ++i) {
        if (((K >> i) & 1) != ((N >> i) & 1)) {
            X.push_back(1 << i);
        }
    }
    if (N <= X.back()) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (auto i = 0; i < N; ++i) {
        if (!ranges::contains(X, i)) {
            cout << i << " ";
        }
    }
    for (auto x : X) {
        cout << x << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

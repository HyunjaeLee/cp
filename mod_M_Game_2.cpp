#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 N, M;
    cin >> N >> M;
    auto x = (N * (N + 1)) % M;
    cout << (1 <= x && x <= N ? "Bob" : "Alice") << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

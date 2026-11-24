#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    array<int, 'Z' + 1> f{};
    ranges::fill(f, -1);
    f['K'] = 0;
    f['R'] = 1;
    f['G'] = 2;
    f['B'] = 4;
    f['Y'] = f['R'] | f['G'];
    f['C'] = f['G'] | f['B'];
    f['M'] = f['R'] | f['B'];
    f['W'] = f['R'] | f['G'] | f['B'];
    int N, T, X, Y;
    cin >> N >> T >> X >> Y;
    auto e = 0;
    for (auto i = 0; i < N; ++i) {
        int x, y;
        char c;
        cin >> x >> y >> c;
        auto d = max(abs(X - x), abs(Y - y));
        if (d <= T) {
            e |= f[c];
        }
    }
    for (char i = 'A'; i <= 'Z'; ++i) {
        if (f[i] == e) {
            cout << i << "\n";
            break;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

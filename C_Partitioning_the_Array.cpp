#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

vector<int> D(int n) {
    vector<int> d;
    for (auto i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            d.push_back(i);
            if (i * i < n) {
                d.push_back(n / i);
            }
        }
    }
    return d;
}

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    copy_n(istream_iterator<int>(cin), N, begin(A));
    auto ans = 0;
    for (auto k : D(N)) {
        auto g = 0;
        for (auto i = 0; i < k; ++i) {
            for (auto j = i + k; j < N; j += k) {
                g = __gcd(g, abs(A[j] - A[j - k]));
            }
        }
        if (1 < g || g == 0) {
            ans += 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

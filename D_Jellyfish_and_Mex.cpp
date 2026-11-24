#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int mex(vector<int> a) {
    ranges::sort(a);
    a.erase(unique(a.begin(), a.end()), a.end());
    for (auto i = 0; i < int(a.size()); ++i) {
        if (a[i] != i) {
            return i;
        }
    }
    return int(a.size());
}

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    auto X = mex(A);
    if (X == 0) {
        cout << "0\n";
        return;
    }
    vector<int> freq(X + 1);
    for (auto i = 0; i < N; ++i) {
        if (A[i] <= X) {
            freq[A[i]] += 1;
        }
    }
    constexpr auto inf = numeric_limits<int>::max() / 2;
    vector<vector<int>> dp(X + 1, vector<int>(X + 1));
    vector<int> pref(X + 1, inf);
    for (auto x = 0; x <= X; ++x) {
        for (auto p = x; p <= X; ++p) {
            if (x == 0) {
                dp[x][p] = max(0, freq[x] - 1) * p;
                continue;
            }
            dp[x][p] = pref[x] + max(0, freq[x] - 1) * p + x;
        }
        for (auto i = 0; i <= X; ++i) {
            pref[i] = min(pref[i], dp[x][i]);
        }
    }
    auto ans = inf;
    for (auto i = 0; i <= X; ++i) {
        ans = min(ans, dp[i][X]);
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

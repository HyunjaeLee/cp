#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N - 1), B(N);
    vector<int> X;
    for (auto i = 0; i < N - 1; ++i) {
        cin >> A[i];
        if (A[i] <= M) {
            X.push_back(A[i]);
        }
    }
    for (auto i = 0; i < N; ++i) {
        cin >> B[i];
        if (B[i] <= M) {
            X.push_back(B[i]);
        }
    }
    X.push_back(1);
    X.push_back(M + 1);
    ranges::sort(A);
    ranges::sort(B);
    ranges::sort(X);
    X.erase(unique(X.begin(), X.end()), X.end());
    vector<int> F(N - 1);
    for (auto i = 0; i < N - 1; ++i) {
        auto it = ranges::upper_bound(B, A[i]);
        F[i] = int(it - B.begin());
    }
    for (auto i = 1; i < N - 1; ++i) {
        F[i] = max(F[i], F[i - 1] + 1);
    }
    vector<vector<i64>> dp(N - 1, vector<i64>(2, -1));
    auto Urushi = [&](auto &&self, int pos, int hit) -> i64 {
        if (N - 1 <= pos)
            return 0;
        auto &ret = dp[pos][hit];
        if (~ret)
            return ret;
        auto f = F[pos] + hit;
        ret = 0;
        if (N <= f) {
            ret = 1;
        }
        if (pos + 1 < N - 1 && f == F[pos + 1]) {
            ret += self(self, pos + 1, 1);
        } else {
            ret += self(self, pos + 1, 0);
        }
        return ret;
    };
    i64 ans = 0;
    vector<i64> pref(N - 1);
    for (auto i = 0; i < N - 1; ++i) {
        pref[i] = int(N <= F[i]);
    }
    for (auto i = 1; i < N - 1; ++i) {
        pref[i] += pref[i - 1];
    }
    for (auto i = 0; i < int(X.size()) - 1; ++i) {
        auto L = X[i], R = X[i + 1];
        auto nxt = int(ranges::upper_bound(A, L) - A.begin());
        auto prv = nxt - 1;
        auto f = int(ranges::upper_bound(B, L) - B.begin());
        i64 sum = 0;
        if (0 <= prv) {
            f = max(F[prv] + 1, f);
            sum = pref[prv];
        }
        sum += int(N <= f);
        if (nxt < N - 1 && F[nxt] == f) {
            sum += Urushi(Urushi, nxt, 1);
        } else {
            sum += Urushi(Urushi, nxt, 0);
        }
        ans += i64(R - L) * sum;
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

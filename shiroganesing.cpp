#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint1000000007;
using i64 = long long;
using i128 = __int128;

optional<Z> dp[101][2020][55];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K, E;
    cin >> N >> K >> E;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    auto f = [&](this auto &&self, int pos, int val, int sum) -> Z {
        if (E < sum)
            return 0;
        if (pos == N - 1)
            return 1;
        if (auto o = dp[pos][val][sum])
            return *o;
        Z ret = 0;
        for (auto nval = max(0, val - K); nval <= val + K; ++nval) {
            ret += self(pos + 1, nval, sum + abs(A[pos + 1] - nval));
        }
        dp[pos][val][sum] = ret;
        return ret;
    };
    auto ans = f(0, 0, A[0]);
    cout << ans.val() << "\n";
}

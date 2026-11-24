#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int dp[5050][5050];

void chmax(int &x, int y) { x = max(x, y); }
void chmin(int &x, int y) { x = min(x, y); }

int game(const string &s) {
    auto n = int(s.size());
    constexpr auto inf = numeric_limits<int>::max() / 2;
    for (auto l = n; 0 <= l; --l) {
        for (auto r = l + 1; r <= n; ++r) {
            auto L = -inf, R = inf;
            if (s[l] == 'B')
                chmax(L, dp[l + 1][r]);
            else
                chmin(R, dp[l + 1][r]);
            if (s[r - 1] == 'B')
                chmax(L, dp[l][r - 1]);
            else
                chmin(R, dp[l][r - 1]);
            if (R <= 0) {
                dp[l][r] = R - 1;
            } else if (0 <= L) {
                dp[l][r] = L + 1;
            } else {
                dp[l][r] = 0;
            }
        }
    }
    return dp[0][n];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    char C;
    cin >> N >> C;
    auto sum = 0;
    for (auto i = 0; i < N; ++i) {
        string s;
        cin >> s;
        sum += game(s);
    }
    if (0 < sum) {
        cout << "B\n";
    } else if (sum < 0) {
        cout << "R\n";
    } else {
        cout << (C == 'B' ? "R\n" : "B\n");
    }
}

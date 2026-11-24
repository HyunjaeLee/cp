#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<string> S(N);
    for (auto i = 0; i < N; ++i) {
        cin >> S[i];
    }
    vector<vector<int>> A(N, vector<int>(M));
    auto f = [&](int r, int c) {
        constexpr array<int, 8> dr{1, -1, 0, 0, 1, -1, 1, -1};
        constexpr array<int, 8> dc{0, 0, 1, -1, 1, 1, -1, -1};
        for (auto i = 0; i < 8; ++i) {
            auto nr = r + dr[i];
            auto nc = c + dc[i];
            if (0 <= nr && nr < N && 0 <= nc && nc < M && S[nr][nc] == '.') {
                A[nr][nc]++;
            }
        }
    };
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (S[i][j] == '#') {
                f(i, j);
            }
        }
    }
    vector<int> v;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            if (S[i][j] == '.') {
                v.push_back(A[i][j]);
            }
        }
    }
    auto sum = 0;
    ranges::sort(v, greater());
    auto ans = 0;
    for (auto x : v) {
        if (K <= sum)
            break;
        ans++;
        sum += x;
    }
    if (sum < K) {
        cout << "-1\n";
        return;
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

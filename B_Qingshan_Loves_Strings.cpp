#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, M;
    cin >> N >> M;
    string S, T;
    cin >> S >> T;
    array<int, 2> cnt{};
    for (auto i = 0; i < N - 1; ++i) {
        if (S[i] == '0' && S[i + 1] == '0') {
            cnt[0] += 1;
        } else if (S[i] == '1' && S[i + 1] == '1') {
            cnt[1] += 1;
        }
    }
    auto good = true;
    for (auto i = 0; i < M - 1; ++i) {
        if (T[i] == T[i + 1]) {
            good = false;
        }
    }
    if (good && (M & 1)) {
        if (T.front() == '0' && T.back() == '0') {
            cnt[1] = 0;
        } else {
            cnt[0] = 0;
        }
    }
    auto bad = cnt[0] + cnt[1];
    string ans;
    if (bad)
        ans = "No";
    else
        ans = "Yes";
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

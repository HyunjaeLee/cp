#include <atcoder/fenwicktree>
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    string S;
    cin >> N >> S;
    vector<int> P(N + 1);
    for (auto i = 0; i < N; ++i) {
        if (S[i] == 'A') {
            P[i + 1] = 1;
        } else if (S[i] == 'B') {
            P[i + 1] = -1;
        }
    }
    for (auto i = 0; i < N; ++i) {
        P[i + 1] += P[i];
    }
    atcoder::fenwick_tree<int> ft(2 * N + 1);
    i64 ans = 0;
    for (auto i = 0; i <= N; ++i) {
        ans += ft.sum(0, P[i] + N);
        ft.add(P[i] + N, 1);
    }
    cout << ans;
}

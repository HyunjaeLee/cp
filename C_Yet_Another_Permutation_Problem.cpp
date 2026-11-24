#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A;
    vector<int> used(N + 1);
    for (auto i = 1; i <= N; ++i) {
        if (used[i])
            continue;
        for (auto x = i; x <= N; x *= 2) {
            if (!used[x]) {
                A.push_back(x);
                used[x] = true;
            }
        }
    }
    for (auto i = 0; i < N; ++i) {
        cout << A[i] << " \n"[i == N - 1];
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

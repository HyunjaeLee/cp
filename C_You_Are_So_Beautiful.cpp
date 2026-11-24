#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    map<int, int> First, Last;
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        if (!First.contains(A[i])) {
            First[A[i]] = i;
        }
        Last[A[i]] = i;
    }
    vector<int> pref(N);
    for (auto i = 0; i < N; ++i) {
        if (First[A[i]] == i) {
            pref[i] = 1;
        }
    }
    for (auto i = 1; i < N; ++i) {
        pref[i] += pref[i - 1];
    }
    i64 ans = 0;
    for (auto i = N - 1; 0 < i; --i) {
        if (Last[A[i]] == i) {
            ans += pref[i - 1];
        }
    }
    for (auto i = 0; i < N; ++i) {
        if (First[A[i]] == Last[A[i]]) {
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

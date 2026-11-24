#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A;
    for (auto i = 0; i < N; ++i) {
        A.push_back(i);
        A.push_back(i);
    }
    for (auto i = 0; i < N; ++i) {
        A.push_back(i);
    }
    for (auto i = 0; i < N; ++i) {
        A.push_back(i);
    }
    cout << A[4 * N - 1] + 1 << " ";
    for (auto i = 0; i < 4 * N - 1; ++i) {
        cout << A[i] + 1 << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

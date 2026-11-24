#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    auto sum = 0LL;
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        sum += A[i];
    }
    auto suff = A;
    for (auto i = N - 1; 0 < i; --i) {
        suff[i - 1] += suff[i];
    }
    for (auto i = 0; i < N; ++i) {
        A[i] = sum / N;
    }
    for (auto i = 0; i < sum % N; ++i) {
        A[N - 1 - i] += 1;
    }
    auto acc = 0LL;
    for (auto i = N - 1; 0 <= i; --i) {
        acc += A[i];
        if (suff[i] < acc) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

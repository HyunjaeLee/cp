#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i64 N, K, X;
    cin >> N >> K >> X;
    vector<i64> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    ranges::sort(A);
    for (auto i = K; i < N; ++i) {
        A[i] = 0;
    }
    auto sum = 0LL;
    for (auto i = 0; i < N; ++i) {
        sum += A[N - 1 - i];
        if (X <= sum) {
            cout << i + 1 << "\n";
            return 0;
        }
    }
    cout << -1 << "\n";
}

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    auto cnt = 0;
    for (auto i = N - 2; 0 <= i; --i) {
        if (A[i] > A[i + 1]) {
            cnt += 1;
            A[i] = A[i + 1];
        }
    }
    cout << cnt << "\n";
    ranges::copy(A, ostream_iterator<int>(cout, " "));
}

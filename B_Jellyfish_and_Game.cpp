#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> A(N);
    vector<int> B(M);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    for (auto i = 0; i < M; ++i) {
        cin >> B[i];
    }
    if (ranges::min(A) < ranges::max(B)) {
        swap(*ranges::min_element(A), *ranges::max_element(B));
    }
    if ((K & 1) == 0 && ranges::min(B) < ranges::max(A)) {
        swap(*ranges::min_element(B), *ranges::max_element(A));
    }
    auto ans = accumulate(begin(A), end(A), 0LL);
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

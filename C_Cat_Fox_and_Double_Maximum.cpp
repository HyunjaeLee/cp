#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

auto F(const vector<int> &P, const vector<int> &Q) {
    auto N = int(size(P));
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        A[i] = P[i] + Q[i];
    }
    auto cnt = 0;
    for (auto i = 1; i < N - 1; ++i) {
        if (A[i - 1] < A[i] && A[i] > A[i + 1]) {
            cnt += 1;
        }
    }
    return cnt;
}

void solve() {
    int N;
    cin >> N;
    vector<int> P(N);
    for (auto i = 0; i < N; ++i) {
        cin >> P[i];
    }
    vector<int> Q(N);
    for (auto i = 0; i < N; ++i) {
        Q[i] = N + 1 - P[i];
    }
    vector<int> I(N + 1);
    for (auto i = 0; i < N; ++i) {
        I[Q[i]] = i;
    }
    auto L = I[N];
    auto W = Q;
    for (auto i = 1; i < L; i += 2) {
        auto t = I[W[i] + 1];
        swap(Q[i], Q[t]);
        I[Q[i]] = i;
        I[Q[t]] = t;
    }
    for (auto i = L + 1; i < N - 1; i += 2) {
        auto t = I[W[i] + 1];
        swap(Q[i], Q[t]);
        I[Q[i]] = i;
        I[Q[t]] = t;
    }
    for (auto i = 0; i < N; ++i) {
        cout << Q[i] << " \n"[i == N - 1];
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

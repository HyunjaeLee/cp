#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<array<i64, 2>> A(N);
    for (auto &[x, y] : A) {
        cin >> x >> y;
    }
    vector<int> used(N);
    vector<int> P{0};
    used[0] = true;
    auto dist = [&](int i, int j) {
        auto dx = A[i][0] - A[j][0];
        auto dy = A[i][1] - A[j][1];
        return dx * dx + dy * dy;
    };
    for (auto i = 0; i < N - 1; ++i) {
        auto p = -1;
        for (auto j = 0; j < N; ++j) {
            if (used[j])
                continue;
            if (p == -1 || dist(P.back(), j) > dist(P.back(), p)) {
                p = j;
            }
        }
        used[p] = true;
        P.push_back(p);
    }
    for (auto i = 0; i < N; ++i) {
        cout << P[i] + 1 << " \n"[i == N - 1];
    }
}

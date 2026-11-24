#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N + 1), B(N + 1);
    for (auto i = 1; i <= N; ++i) {
        cin >> A[i];
    }
    auto dfs = [&](auto &&self, int u, int x) -> int {
        if (2 * u + 1 <= N) {
            auto best = min({x, A[2 * u], A[2 * u + 1]});
            B[u] = best;
            if (x == best) {
                self(self, 2 * u, A[2 * u]);
                self(self, 2 * u + 1, A[2 * u + 1]);
                return u;
            } else if (A[2 * u] == best) {
                self(self, 2 * u + 1, A[2 * u + 1]);
                return self(self, 2 * u, x);
            } else {
                if (x < A[2 * u]) {
                    auto l = self(self, 2 * u, x);
                    auto r = self(self, 2 * u + 1, x);
                    if (l < r) { // LR
                        self(self, 2 * u + 1, A[2 * u]);
                        return l;
                    } else { // R
                        self(self, 2 * u, A[2 * u]);
                        return r;
                    }
                } else {
                    auto l = self(self, 2 * u, A[2 * u]);
                    auto r = self(self, 2 * u + 1, A[2 * u]);
                    if (l < r) { // R
                        return self(self, 2 * u + 1, x);
                    } else { // LR
                        return self(self, 2 * u, x);
                    }
                }
            }
        } else if (2 * u <= N) {
            B[u] = min(A[2 * u], x);
            if (A[2 * u] < x) {
                return self(self, 2 * u, x);
            } else {
                self(self, 2 * u, A[2 * u]);
                return u;
            }
        } else {
            B[u] = x;
            return u;
        }
    };
    dfs(dfs, 1, A[1]);
    for (auto i = 1; i <= N; ++i) {
        cout << B[i] << " \n"[i == N];
    }
}

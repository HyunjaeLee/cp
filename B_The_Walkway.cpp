#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    i64 N, M, D;
    cin >> N >> M >> D;
    vector<i64> S(M + 2);
    for (auto i = 0; i < M; ++i) {
        cin >> S[i + 1];
    }
    S[0] = 1;
    S[M + 1] = N;
    i64 X = 1;
    for (auto i = 0; i < M + 1; ++i) {
        auto d = S[i + 1] - S[i];
        X += d / D;
        if (d % D && i + 1 < M + 1) {
            X += 1;
        }
    }
    auto P = 0LL;
    for (auto i = 1; i < M + 1; ++i) {
        auto p = 0LL;
        auto d = S[i + 1] - S[i - 1];
        p += d / D;
        if (d % D && i + 1 < M + 1) {
            p += 1;
        }

        d = S[i + 1] - S[i];
        p -= d / D;
        if (d % D && i + 1 < M + 1) {
            p -= 1;
        }

        d = S[i] - S[i - 1];
        p -= d / D;
        if (d % D && i < M + 1) {
            p -= 1;
        }

        P = min(P, p);
    }
    auto Y = 0;
    for (auto i = 1; i < M + 1; ++i) {
        auto p = 0LL;
        auto d = S[i + 1] - S[i - 1];
        p += d / D;
        if (d % D && i + 1 < M + 1) {
            p += 1;
        }

        d = S[i + 1] - S[i];
        p -= d / D;
        if (d % D && i + 1 < M + 1) {
            p -= 1;
        }

        d = S[i] - S[i - 1];
        p -= d / D;
        if (d % D && i < M + 1) {
            p -= 1;
        }

        if (P == p)
            Y += 1;
    }
    X += P;
    cout << X << " " << Y << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

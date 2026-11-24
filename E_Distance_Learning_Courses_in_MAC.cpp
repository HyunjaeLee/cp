#include <bits/stdc++.h>
using namespace std;
using i8 = signed char;
using i64 = long long;
using i128 = __int128;

struct S {
    int cnt[30][4]{};
    int who[30][4]{};
};

S op(S a, S b) {
    S r;
    for (auto i = 0; i < 30; ++i) {
        for (auto j = 0; j < 4; ++j) {
            r.cnt[i][j] = a.cnt[i][j] + b.cnt[i][j];
            r.who[i][j] = a.who[i][j] ^ b.who[i][j];
        }
    }
    return r;
}

S e() { return {}; }

S inv(S a) {
    for (auto i = 0; i < 30; ++i) {
        for (auto j = 0; j < 4; ++j) {
            a.cnt[i][j] *= -1;
        }
    }
    return a;
}

void solve() {
    int N;
    cin >> N;
    vector<int> X(N), Y(N);
    for (auto i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }
    vector<S> A(N);
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < 30; ++j) {
            auto ub = (Y[i] >> j) & 1;
            auto lb = (X[i] >> j) & 1;
            A[i].cnt[j][(ub << 1) | lb] = 1;
            A[i].who[j][(ub << 1) | lb] = i;
        }
    }
    for (auto i = 1; i < N; ++i) {
        A[i] = op(A[i], A[i - 1]);
    }
    auto prod = [&](int l, int r) {
        if (l == 0)
            return A[r - 1];
        return op(A[r - 1], inv(A[l - 1]));
    };
    int Q;
    cin >> Q;
    while (Q--) {
        int L, R;
        cin >> L >> R;
        --L;
        auto [cnt, who] = prod(L, R);
        auto ans = 0;
        for (auto p = 29; 0 <= p; --p) {
            // step 1
            if (1 <= cnt[p][0b11] || 1 <= cnt[p][0b10]) {
                ans |= 1 << p;
            }
            // step 2
            if ((1 <= cnt[p][0b11] && 1 <= cnt[p][0b10]) || 2 <= cnt[p][0b10]) {
                ans |= (1 << p) - 1;
            }
            // step 3
            if (cnt[p][0b11] == 0 && 1 == cnt[p][0b10]) {
                auto i = who[p][0b10];
                auto b = Y[i] & ((1 << p) - 1);
                if (0 < b) {
                    auto q = __lg(b);
                    auto ub = (Y[i] >> q) & 1;
                    auto lb = (X[i] >> q) & 1;
                    cnt[q][(ub << 1) | lb] -= 1;
                    who[q][(ub << 1) | lb] ^= i;
                    cnt[q][0b10] += 1;
                    who[q][0b10] ^= i;
                }
            }
        }
        cout << ans << " ";
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

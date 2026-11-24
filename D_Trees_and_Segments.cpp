#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

struct Line {
    mutable i64 k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(i64 x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const i64 inf = LLONG_MAX;
    i64 div(i64 a, i64 b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end())
            return x->p = inf, 0;
        if (x->k == y->k)
            x->p = x->m > y->m ? inf : -inf;
        else
            x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(i64 k, i64 m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    i64 query(i64 x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

void solve() {
    int N, K;
    string S;
    cin >> N >> K >> S;
    vector<vector<int>> A(N + 1, vector<int>(K + 2));
    vector<vector<int>> B(N + 1, vector<int>(K + 2));
    for (auto i = 0; i < N; ++i) {
        auto cost = 0;
        for (auto j = i; j < N; ++j) {
            if (S[j] == '0') {
                cost += 1;
            }
            if (cost <= K) {
                A[i][cost] = max(A[i][cost], j - i + 1);
                B[j][cost] = max(B[j][cost], j - i + 1);
            }
        }
    }
    for (auto i = N - 1; 0 <= i; --i) {
        for (auto j = 0; j <= K; ++j) {
            A[i][j] = max({A[i][j], A[i + 1][j], (0 <= j - 1 ? A[i][j - 1] : 0)});
        }
    }
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j <= K; ++j) {
            B[i][j] = max({B[i][j], (0 <= i - 1 ? B[i - 1][j] : 0), (0 <= j - 1 ? B[i][j - 1] : 0)});
        }
    }
    LineContainer F;
    F.add(0, A[0][K]);
    for (auto i = 0; i < N; ++i) {
        auto cost = 0;
        for (auto j = i; j < N; ++j) {
            if (S[j] == '1') {
                cost += 1;
            }
            if (cost <= K) {
                auto a = A[j + 1][K - cost];
                auto b = 0 <= i - 1 ? B[i - 1][K - cost] : 0;
                F.add(j - i + 1, max(a, b));
            }
        }
    }
    for (auto i = 1; i <= N; ++i) {
        cout << F.query(i) << " ";
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

#include <atcoder/scc>
#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */

typedef vector<double> vd;

auto operator/(vd a, double k) {
    auto n = int(a.size());
    for (auto i = 0; i < n; ++i) {
        a[i] = a[i] / k;
    }
    return a;
}

auto operator-(vd a, vd b) {
    auto n = int(a.size());
    for (auto i = 0; i < n; ++i) {
        a[i] = a[i] - b[i];
    }
    return a;
}

auto operator*(double k, vd a) {
    auto n = int(a.size());
    for (auto i = 0; i < n; ++i) {
        a[i] = k * a[i];
    }
    return a;
}

int solveLinear(vector<vd> &A, vector<vd> &b, vector<vd> &x) {
    int n = sz(A), m = sz(x), rank = 0, br = -1, bc = -1;
    if (n)
        assert(sz(A[0]) == m);
    vi col(m);
    iota(all(col), 0);

    rep(i, 0, n) {
        double v, bv = 0;
        rep(r, i, n) rep(c, i, m) if ((v = fabs(A[r][c])) > bv) br = r, bc = c, bv = v;
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        rep(j, 0, n) swap(A[j][i], A[j][bc]);
        bv = 1 / A[i][i];
        rep(j, i + 1, n) {
            double fac = A[j][i] * bv;
            b[j] = b[j] - fac * b[i];
            rep(k, i + 1, m) A[j][k] -= fac * A[i][k];
        }
        rank++;
    }

    // x.assign(m, 0);
    for (int i = rank; i--;) {
        b[i] = b[i] / A[i][i];
        x[col[i]] = b[i];
        rep(j, 0, i) b[j] = b[j] - A[j][i] * b[i];
    }
    return rank; // (multiple solutions if rank < m)
}

void solve() {
    int C, P;
    cin >> C >> P;
    vector<vector<double>> W(C, vector<double>(C));
    vector<vector<double>> V(C, vector<double>(P));
    for (auto i = 0; i < C; ++i) {
        int k;
        cin >> k;
        for (auto j = 0; j < k; ++j) {
            string s;
            cin >> s;
            auto pos = s.find(":");
            auto x = stoi(s.substr(1, pos - 1)) - 1;
            if (s[0] == 'P') {
                V[i][x] = stod(s.substr(pos + 1)) / 100.0;
            } else {
                W[i][x] = stod(s.substr(pos + 1)) / 100.0;
            }
        }
    }
    atcoder::scc_graph g(C);
    vector<vector<int>> adj(C);
    for (auto i = 0; i < C; ++i) {
        for (auto j = 0; j < C; ++j) {
            if (0 < W[i][j]) {
                g.add_edge(i, j);
                adj[i].push_back(j);
            }
        }
    }
    auto scc = g.scc();
    vector<int> id(C);
    for (auto i = 0; i < int(scc.size()); ++i) {
        for (auto u : scc[i]) {
            id[u] = i;
        }
    }
    vector<vector<double>> X(C, vector<double>(P));
    for (auto f = int(scc.size()) - 1; 0 <= f; --f) {
        auto k = int(scc[f].size());
        vector<vector<double>> a(k, vector<double>(k));
        vector<vd> x(k, vd(P)), v(k, vd(P));
        for (auto s = 0; s < k; ++s) {
            a[s][s] = 1;
        }
        for (auto s = 0; s < k; ++s) {
            for (auto t = 0; t < k; ++t) {
                a[s][t] -= W[scc[f][s]][scc[f][t]];
            }
        }
        for (auto s = 0; s < k; ++s) {
            for (auto p = 0; p < P; ++p) {
                auto i = scc[f][s];
                v[s][p] = V[i][p];
                for (auto j : adj[i]) {
                    v[s][p] += W[i][j] * X[j][p];
                }
            }
        }
        solveLinear(a, v, x);
        for (auto s = 0; s < k; ++s) {
            for (auto p = 0; p < P; ++p) {
                auto i = scc[f][s];
                X[i][p] = x[s][p];
            }
        }
    }
    cout << fixed << setprecision(6);
    for (auto x : X) {
        show(x);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}

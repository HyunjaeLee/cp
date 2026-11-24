#include <atcoder/dsu>
#include <atcoder/lazysegtree>
#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

int op(int a, int b) { return max(a, b); }

int e() { return 0; }

int mapping(int f, int x) { return f + x; }

int composition(int f, int g) { return f + g; }

int id() { return 0; }

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    A.resize(2 * N);
    for (auto i = 0; i < N; ++i) {
        --A[i];
        A[N + i] = A[i];
    }
    vector<int> F(N, -1);
    vector<vector<int>> T(2 * N);
    for (auto i = 2 * N - 1; 0 <= i; --i) {
        if (A[i] + 1 < N && 0 <= F[A[i] + 1]) {
            T[i].push_back(F[A[i] + 1]);
        }
        if (0 <= A[i] - 1 && 0 <= F[A[i] - 1]) {
            T[i].push_back(F[A[i] - 1]);
        }
        F[A[i]] = i;
    }
    vector<int> color(N);
    vector<int> v(N);
    auto nodes = 0;
    auto edges = 0;
    atcoder::dsu dsu(N);
    for (auto i = 0; i < N; ++i) {
        color[A[i]] = 1;
        nodes += 1;
        if (A[i] + 1 < N && color[A[i] + 1] && !dsu.same(A[i], A[i] + 1)) {
            dsu.merge(A[i], A[i] + 1);
            edges += 1;
        }
        if (0 <= A[i] - 1 && color[A[i] - 1] && !dsu.same(A[i], A[i] - 1)) {
            dsu.merge(A[i], A[i] - 1);
            edges += 1;
        }
        v[i] = nodes - edges;
    }
    v.resize(2 * N, 1);
    atcoder::lazy_segtree<int, op, e, int, mapping, composition, id> seg(v);
    auto ans = 0;
    for (auto i = 0; i < N; ++i) {
        if (seg.prod(i, i + N) <= 2) {
            ans += 1;
        }
        ranges::sort(T[i]);
        if (1 <= T[i].size()) {
            auto p = T[i][0];
            seg.apply(i, p, -1);
        }
        if (2 <= T[i].size()) {
            auto q = T[i][1];
            seg.apply(q, i + N, 1);
        }
    }
    cout << ans << "\n";
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

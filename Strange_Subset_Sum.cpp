#define NDEBUG
#include <atcoder/convolution>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

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

int subset_sum(int N, const vector<int> &S) {
    assert(ssize(S) == N / 2);
    vector<int> A(N), B(2 * N), C(3 * N);
    for (auto x : S) {
        A[x] = B[2 * x] = C[3 * x] = 1;
    }
    auto P = convolution(A, convolution(A, A));
    auto Q = convolution(A, B);
    auto R = C;
    auto ans = P[N] - 3 * Q[N] + 2 * R[N];
    return ans;
}

#define TC
void solve() {
    int N;
    cin >> N;
    auto query = [&](int a) {
        assert(1 <= a && a <= N - 1);
        cout << "? " << a << endl;
        string r;
        cin >> r;
        if (r[0] == '-')
            exit(0);
        return r[0] == 'Y';
    };
    auto answer = [&](int ans) { cout << "! " << ans << endl; };
    vector<int> color(N, -1);
    if (N % 2 == 0) {
        color[N / 2] = query(N / 2);
        if (color[N / 2] == 0) {
            answer(2);
            return;
        }
    }
    array<int, 2> cnt{};
    for (auto i = 1; i < (N + 1) / 2; ++i) {
        color[i] = query(i);
        cnt[color[i]]++;
    }
    auto f = cnt[0] < cnt[1] ? 0 : 1;
    for (auto i = 1; i < (N + 1) / 2; ++i) {
        if (color[i] == f) {
            color[N - i] = query(N - i);
            if (color[N - i] == f) {
                answer(2);
                return;
            }
        }
    }
    for (auto i = 1; i < (N + 1) / 2; ++i) {
        if (color[i] != f) {
            color[N - i] = f;
        }
    }
    vector<int> S;
    for (auto i = 1; i < N; ++i) {
        assert(color[i] == 0 || color[i] == 1);
        if (color[i]) {
            S.push_back(i);
        }
    }
    if (subset_sum(N, S)) {
        answer(3);
    } else {
        answer(-1);
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

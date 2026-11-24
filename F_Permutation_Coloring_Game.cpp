#include <atcoder/dsu>
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

vector<int> decompose(const vector<int> &A) {
    auto N = int(size(A));
    atcoder::dsu dsu(N);
    for (auto i = 0; i < N; ++i) {
        dsu.merge(i, A[i]);
    }
    vector<int> C;
    for (auto i = 0; i < N; ++i) {
        if (i == dsu.leader(i)) {
            C.push_back(dsu.size(i));
        }
    }
    return C;
}

int dp[50][25][25];

#define TC
void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> P(N);
    read<1>(P);
    auto A = decompose(P);
    ranges::sort(A, greater());
    if (K == 1) {
        if (3 <= A[0]) {
            cout << "Bob\n";
            return;
        }
        if (1 == A[0]) {
            cout << "Alice\n";
            return;
        }
        cout << (ranges::count(A, 1) % (K + 1) ? "Alice\n" : "Bob\n");
        return;
    }
    if (K + 2 <= A[0]) {
        cout << "Bob\n";
        return;
    }
    if (2 <= size(A) && A[0] == K + 1 && A[1] == K + 1) {
        cout << "Bob\n";
        return;
    }
    if (A[0] == K + 1) {
        if (size(A) == 1) {
            cout << "Bob\n";
            return;
        }
        if (2 <= size(A) && A[1] == 1) {
            cout << (ranges::count(A, 1) % (K + 1) ? "Alice\n" : "Bob\n");
            return;
        }
        auto sum = 0;
        auto afford = 0;
        for (auto i = 1; i < ssize(A); ++i) {
            if (2 <= A[i]) {
                if (K < sum + A[i]) {
                    cout << "Bob\n";
                    return;
                }
                sum += A[i];
            } else {
                if (sum + 1 <= K) {
                    sum += 1;
                    afford += 1;
                }
            }
        }
        auto cnt = ranges::count(A, 1);
        for (auto i = 0; i <= afford; ++i) {
            if ((cnt - i) % (K + 1) == 0) {
                cout << "Alice\n";
                return;
            }
        }
        cout << "Bob\n";
        return;
    }
    memset(dp, -1, sizeof dp);
    auto f = [&](this auto &&self, int pos, int cnt, int bag) -> int {
        assert(pos <= ssize(A) && cnt <= K && bag <= K);
        if (pos == ssize(A))
            return 0;
        if (cnt == K)
            return 0;
        auto &ret = dp[pos][cnt][bag];
        if (~ret)
            return ret;
        ret = A[pos] - 1 + self(pos + 1, cnt + 1, bag);
        if (A[pos] + bag <= K) {
            ret = min(ret, self(pos + 1, cnt, bag + A[pos]));
        }
        return ret;
    };
    if (K < f(0, 0, 0)) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
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

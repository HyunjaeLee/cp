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

auto cntq = 0;

int query(int i) {
    assert(cntq++ <= 1000);
    cout << "? " << i + 1 << endl;
    int r;
    cin >> r;
    return r;
}

void answer(int i) { cout << "! " << i + 1 << endl; }

void solve() {
    int N, K;
    cin >> N >> K;
    auto S = int(sqrt(double(N)));
    mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> dist(0, N - 1);
    auto p = dist(g);
    auto x = query(p);
    auto found = false;
    for (auto t = 0; t < 2 * S; ++t) {
        auto q = (p + S) % N;
        auto y = query(q);
        if (x < y) {
            found = true;
            break;
        }
        p = q;
        x = y;
    }
    assert(found);
    p = (N + p - 1) % N;
    x = query(p);
    for (auto d = 0; d < S + 10; ++d) {
        auto q = (p + 1) % N;
        auto y = query(q);
        if (x < y) {
            answer(q);
            return;
        }
        p = q;
        x = y;
    }
    assert(0);
}

// void test() {
//     auto N = 4;
//     auto K = 4; // even number
//     vector<int> A(N, K);
//     show(A);
//     auto T = 20;
//     auto P = 1;
//     while (T--) {
//         vector<int> B(N);
//         for (auto i = 0; i < N; ++i) {
//             auto l = (i - 1 + N) % N;
//             auto r = (i + 1) % N;
//             if (i == P) {
//                 B[r] += A[i];
//             } else {
//                 B[l] += floor_div(A[i], 2);
//                 B[r] += ceil_div(A[i], 2);
//             }
//         }
//         swap(A, B);
//         show(A);
//     }
// }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    // test();
    // return 0;
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}

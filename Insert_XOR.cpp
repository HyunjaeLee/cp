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
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    auto G = 1;
    array<int, 2> cnt{N, 0};
    auto touch = [&](int p) {
        auto l = 0 <= p - 2 && A[p - 2] == 0 && A[p - 1] == 0;
        auto r = p + 2 < N && A[p + 1] == 0 && A[p + 2] == 0;
        if (l && r) {
            G += A[p] ? -1 : 1;
        } else if (l || r) {
            //
        } else {
            l = 0 <= p - 1 && A[p - 1] == 0;
            r = p + 1 < N && A[p + 1] == 0;
            if (A[p]) {
                G += (l || r) ? 1 : 0;
            } else {
                G += (l || r) ? -1 : 0;
            }
        }
        cnt[A[p]]--;
        A[p] ^= 1;
        cnt[A[p]]++;
    };
    for (auto i = 0; i < N; ++i) {
        int x;
        cin >> x;
        if (x) {
            touch(i);
        }
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int i;
        cin >> i;
        --i;
        touch(i);
        auto ans = 0;
        if (G == 0) {
            if (cnt[1] == N) {
                ans = N;
            } else if (A[0] == 0 && A[N - 1] == 0) {
                ans = 3;
            } else {
                ans = 2;
            }
        } else {
            ans = 3 * G - 1;
            if (pair{A[0], A[1]} == pair{0, 0}) {
                //
            } else {
                if (A[0] == 0) {
                    ans += 2;
                } else {
                    ans += 1;
                }
            }
            if (pair{A[N - 2], A[N - 1]} == pair{0, 0}) {
                //
            } else {
                if (A[N - 1] == 0) {
                    ans += 2;
                } else {
                    ans += 1;
                }
            }
        }
        cout << ans << "\n";
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

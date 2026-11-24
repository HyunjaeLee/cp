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

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
        --A[i];
    }
    auto hello = [&] {
        vector<int> ans(N);
        for (auto i = 0; i < N; ++i) {
            if (A[i] < i) {
                ++ans[0];
            }
        }
        vector<int> T(N + 1);
        for (auto i = 0; i < N; ++i) {
            if (A[i] != N - 1)
                ++T[(i - A[i] + N) % N];
        }
        for (auto i = 1; i < N; ++i) {
            auto cnt = ans[i - 1];
            if (A[i - 1] != N - 1) {
                ++cnt;
            }
            cnt -= T[i];
            ans[i] = cnt;
        }
        return ans;
    };
    auto ans = hello();
    ranges::reverse(A);
    auto ans_rev = hello();
    cout << ans[0] << "\n";
    int Q;
    cin >> Q;
    auto d = 0;
    auto flip = 0;
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k;
            cin >> k;
            d = (d + k) % N;
        } else if (t == 2) {
            int k;
            cin >> k;
            d = (d - k + N) % N;
        } else {
            d = (N - d) % N;
            flip ^= 1;
        }
        cout << (flip ? ans_rev[d] : ans[d]) << "\n";
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

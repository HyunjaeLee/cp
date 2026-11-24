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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<int> freq(N + 2);
    for (auto i = 0; i < N; ++i) {
        if (A[i] < N + 2) {
            freq[A[i]]++;
        }
    }
    auto mex = -1;
    for (auto i = 0; i <= N; ++i) {
        if (freq[i] == 0) {
            mex = i;
            break;
        }
    }
    if (freq[mex] == 0 && freq[mex + 1] == 0) {
        for (auto i = 0; i <= N; ++i) {
            if (2 <= freq[i] || mex < i) {
                cout << "Yes\n";
                return;
            }
        }
        cout << "No\n";
    } else {
        vector<int> I;
        for (auto i = 0; i < N; ++i) {
            if (A[i] == mex + 1) {
                I.push_back(i);
            }
        }
        for (auto i = I.front(); i <= I.back(); ++i) {
            A[i] = mex;
        }
        freq.assign(N + 2, 0);
        for (auto i = 0; i < N; ++i) {
            if (A[i] < N + 2) {
                freq[A[i]]++;
            }
        }
        auto bear = -1;
        for (auto i = 0; i <= N; ++i) {
            if (freq[i] == 0) {
                bear = i;
                break;
            }
        }
        if (bear == mex + 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
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

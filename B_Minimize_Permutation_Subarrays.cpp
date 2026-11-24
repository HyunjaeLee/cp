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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    vector<int> I;
    vector<int> V;
    for (auto i = 0; i < N; ++i) {
        if (A[i] == 1 || A[i] == 2 || A[i] == N) {
            I.push_back(i + 1);
            V.push_back(A[i]);
        }
    }
    if (V == vector{1, 2, N}) {
        cout << I[1] << " " << I[2] << "\n";
    } else if (V == vector{2, 1, N}) {
        cout << I[1] << " " << I[2] << "\n";
    } else if (V == vector{N, 1, 2}) {
        cout << I[0] << " " << I[1] << "\n";
    } else if (V == vector{N, 2, 1}) {
        cout << I[0] << " " << I[1] << "\n";
    } else {
        cout << I[0] << " " << I[0] << "\n";
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

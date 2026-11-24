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
    string S;
    cin >> N >> S;
    vector<int> P, Q;
    for (auto i = 0; i < N; ++i) {
        if (S[i] == '1') {
            P.push_back(i);
        } else {
            Q.push_back(i);
        }
    }
    string A(N, '(');
    string B(N, '(');
    for (auto i = 0; i < int(P.size()); ++i) {
        if (i < int(P.size()) / 2) {
            A[P[i]] = '(';
            B[P[i]] = '(';
        } else {
            A[P[i]] = ')';
            B[P[i]] = ')';
        }
    }
    auto check = [&](string s) {
        auto stk = 0;
        for (auto i = 0; i < N; ++i) {
            if (s[i] == '(') {
                stk++;
            } else {
                stk--;
                if (stk < 0) {
                    return false;
                }
            }
        }
        return stk == 0;
    };
    for (auto i = 0; i < int(Q.size()); ++i) {
        if (i & 1) {
            A[Q[i]] = '(';
            B[Q[i]] = ')';
        } else {
            A[Q[i]] = ')';
            B[Q[i]] = '(';
        }
    }
    if (check(A) && check(B))
        cout << "YES\n" << A << "\n" << B << "\n";
    else
        cout << "NO\n";
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

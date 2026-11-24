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
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    set<int> A, B;
    auto Add = [&](int i) {
        if (i < 0 || N <= i)
            return;
        if (S[i] == '(') {
            if (i + 1 < N && S[i + 1] == '(') {
                A.insert(i);
            }
        } else {
            if (0 <= i - 1 && S[i - 1] == ')') {
                B.insert(i);
            }
        }
    };
    auto Erase = [&](int i) {
        if (i < 0 || N <= i)
            return;
        if (S[i] == '(') {
            if (i + 1 < N && S[i + 1] == '(') {
                A.erase(i);
            }
        } else {
            if (0 <= i - 1 && S[i - 1] == ')') {
                B.erase(i);
            }
        }
    };
    for (auto i = 0; i < N; ++i) {
        Add(i);
    }
    auto Fun = [&] {
        if (S[0] == ')' || S[N - 1] == '(' || N % 2 == 1) {
            return false;
        }
        auto l = -1;
        if (!A.empty())
            l = *A.begin();
        auto r = -1;
        if (!B.empty())
            r = *B.rbegin();
        if (l == -1 && r == -1)
            return true;
        if (l == -1 || r == -1)
            return false;
        if (l % 2 != 0 || (N - r - 1) % 2 != 0)
            return false;
        if (B.lower_bound(l) != B.begin())
            return false;
        if (A.lower_bound(r) != A.end())
            return false;
        auto len = (r - l + 1);
        return len % 2 == 0;
    };
    while (Q--) {
        int i;
        cin >> i;
        --i;
        Erase(i - 1);
        Erase(i);
        Erase(i + 1);
        S[i] = (S[i] == ')' ? '(' : ')');
        Add(i - 1);
        Add(i);
        Add(i + 1);
        cout << (Fun() ? "YES\n" : "NO\n");
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

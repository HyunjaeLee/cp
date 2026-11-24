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

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N), B(N);
    multiset<int> S1, S2, L, R;
    i64 sum = 0, total = 0;
    auto Balance = [&] {
        while (ssize(L) < ssize(S1)) {
            auto it = R.begin();
            sum += *it;
            L.insert(*it);
            R.erase(it);
        }
        while (ssize(L) > ssize(S1)) {
            auto it = prev(L.end());
            sum -= *it;
            R.insert(*it);
            L.erase(it);
        }
    };
    auto Erase = [&](int i) {
        total -= A[i];
        if (B[i] == 1) {
            auto it = S1.find(A[i]);
            S1.erase(it);
        } else {
            auto it = S2.find(A[i]);
            S2.erase(it);
        }
        if (L.contains(A[i])) {
            sum -= A[i];
            auto it = L.find(A[i]);
            L.erase(it);
        } else {
            auto it = R.find(A[i]);
            R.erase(it);
        }
        Balance();
    };
    auto Insert = [&](int i, int a, int b) {
        A[i] = a;
        B[i] = b;
        total += A[i];
        if (B[i] == 1) {
            S1.insert(A[i]);
        } else {
            S2.insert(A[i]);
        }
        if (L.empty() || *L.rbegin() < A[i]) {
            R.insert(A[i]);
        } else {
            L.insert(A[i]);
            sum += A[i];
        }
        Balance();
    };
    for (auto i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
        Insert(i, A[i], B[i]);
    }
    while (Q--) {
        int i, a, b;
        cin >> i >> a >> b;
        --i;
        Erase(i);
        Insert(i, a, b);
        i64 ans;
        if (S1.empty()) {
            ans = 2 * total - *S2.begin();
        } else if (S2.empty()) {
            ans = total;
        } else {
            if (*S2.begin() <= *S1.rbegin()) {
                ans = 2 * total - sum;
            } else {
                ans = 2 * total - (sum - *S1.rbegin() + *S2.begin());
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

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

#ifndef CEIL_DIV_HPP
#define CEIL_DIV_HPP

template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }

#endif // CEIL_DIV_HPP

void solve() {
    i64 N, A, B;
    cin >> N >> A >> B;
    if (N < A) {
        cout << "No\n";
        return;
    }
    auto C = N * ceil_div(N, 2LL);
    for (auto i = 0; i < A; ++i) {
        if (i < N / 2) {
            C -= ceil_div(N, 2LL);
        } else {
            C -= N - i;
            C -= ceil_div(N, 2LL) - (i - N / 2);
            C += 1;
        }
    }
    if (B <= C) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

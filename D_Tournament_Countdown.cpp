#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

#ifndef CEIL_DIV_HPP
#define CEIL_DIV_HPP

template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }

#endif // CEIL_DIV_HPP

void solve() {
    int N;
    cin >> N;
    if (N == -1)
        exit(0);
    auto cnt = 0;
    auto query = [&](int a, int b) {
        cnt += 1;
        assert(cnt <= ceil_div(1 << (N + 1), 3));
        cout << "? " << a + 1 << " " << b + 1 << endl;
        int r;
        cin >> r;
        if (r == -1)
            exit(0);
        return r;
    };
    vector<int> A(1 << N);
    iota(begin(A), end(A), 0);
    for (auto m = N; 1 < m; --m) {
        vector<int> B;
        for (auto i = 0; i < (1 << m); i += 4) {
            auto a = A[i], b = A[i + 1], c = A[i + 2], d = A[i + 3];
            auto r = query(a, c);
            if (r == 0) { // =
                B.push_back(b);
                B.push_back(d);
            } else if (r == 1) { // >
                B.push_back(a);
                if (query(c, d) == 1) {
                    B.push_back(c);
                } else {
                    B.push_back(d);
                }
            } else { // <
                B.push_back(c);
                if (query(a, b) == 1) {
                    B.push_back(a);
                } else {
                    B.push_back(b);
                }
            }
        }
        swap(A, B);
    }
    assert(A.size() == 2);
    int ans;
    if (query(A[0], A[1]) == 1) {
        ans = A[0] + 1;
    } else {
        ans = A[1] + 1;
    }
    cout << "! " << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

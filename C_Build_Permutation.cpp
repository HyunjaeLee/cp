#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    iota(begin(A), end(A), 0);
    auto F = [&](auto &&self, int n) -> void {
        if (n == 0)
            return;
        auto p = -1;
        for (auto i = 0; i < n; ++i) {
            auto x = i + n - 1;
            auto s = int(sqrt(x));
            if (s * s == x) {
                p = i;
            }
        }
        assert(p != -1);
        reverse(A.begin() + p, A.begin() + n);
        self(self, p);
    };
    F(F, N);
    for (auto i = 0; i < N; ++i) {
        cout << A[i] << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

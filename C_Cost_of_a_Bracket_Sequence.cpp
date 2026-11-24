#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        if (S[i] == '(') {
            A[i] = 1;
        } else {
            A[i] = -1;
        }
    }
    auto eval = [&](const vector<int> &removed) {
        auto stk = 0;
        auto ans = N;
        for (auto i = 0; i < N; ++i) {
            if (removed[i]) {
                ans -= 1;
                continue;
            }
            if (A[i] == 1) {
                stk += 1;
            } else {
                if (stk == 0) {
                    ans -= 1;
                } else {
                    stk -= 1;
                }
            }
        }
        ans -= stk;
        return ans;
    };
    auto F = [&](int L, int R) {
        vector<int> removed(N);
        for (auto i = 0; i < N; ++i) {
            if (A[i] == 1 && 0 < L) {
                L -= 1;
                removed[i] = 1;
            }
        }
        for (auto i = N - 1; 0 <= i; --i) {
            if (A[i] == -1 && 0 < R) {
                R -= 1;
                removed[i] = 1;
            }
        }
        return removed;
    };
    auto ans = numeric_limits<int>::max();
    vector<int> removed;
    for (auto l = 0; l <= K; ++l) {
        auto r = K - l;
        auto v = F(l, r);
        auto score = eval(v);
        if (score < ans) {
            ans = score;
            removed = std::move(v);
        }
    }
    for (auto i = 0; i < N; ++i) {
        cout << removed[i];
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

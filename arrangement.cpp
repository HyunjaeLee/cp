#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    string S;
    cin >> S;
    auto OK = 3 <= N && 0 < ranges::count(S, 'E') && 0 < ranges::count(S, 'H');
    if (not OK) {
        cout << "-1\n";
        return;
    }
    vector<int> P, Q;
    for (auto i = 0; i < N; ++i) {
        if (S[i] == 'H') {
            P.push_back(A[i]);
        } else {
            Q.push_back(A[i]);
        }
    }
    ranges::sort(P);
    ranges::sort(Q);
    constexpr auto inf = numeric_limits<int>::max() / 2;
    auto pred = [&](int X) {
        {
            auto L = inf, R = -inf;
            auto it1 = ranges::upper_bound(P, P[0] + X);
            if (it1 != P.end()) {
                auto l = *it1;
                auto r = P.back();
                L = min(L, l);
                R = max(R, r);
            }
            auto it2 = ranges::upper_bound(Q, Q[0] + X);
            if (it2 != Q.end()) {
                auto l = *it2;
                auto r = Q.back();
                L = min(L, l);
                R = max(R, r);
            }
            if (R - L <= X)
                return 0;
        }
        {
            auto L = inf, R = -inf;
            auto it1 = ranges::lower_bound(P, P.back() - X);
            if (it1 != P.begin()) {
                auto l = P[0];
                auto r = *prev(it1);
                L = min(L, l);
                R = max(R, r);
            }
            auto it2 = ranges::upper_bound(Q, Q[0] + X);
            if (it2 != Q.end()) {
                auto l = *it2;
                auto r = Q.back();
                L = min(L, l);
                R = max(R, r);
            }
            if (R - L <= X)
                return 0;
        }
        {
            auto L = inf, R = -inf;
            auto it1 = ranges::upper_bound(P, P[0] + X);
            if (it1 != P.end()) {
                auto l = *it1;
                auto r = P.back();
                L = min(L, l);
                R = max(R, r);
            }
            auto it2 = ranges::lower_bound(Q, Q.back() - X);
            if (it2 != Q.begin()) {
                auto l = Q[0];
                auto r = *prev(it2);
                L = min(L, l);
                R = max(R, r);
            }
            if (R - L <= X)
                return 0;
        }
        {
            auto L = inf, R = -inf;
            auto it1 = ranges::lower_bound(P, P.back() - X);
            if (it1 != P.begin()) {
                auto l = P[0];
                auto r = *prev(it1);
                L = min(L, l);
                R = max(R, r);
            }
            auto it2 = ranges::lower_bound(Q, Q.back() - X);
            if (it2 != Q.begin()) {
                auto l = Q[0];
                auto r = *prev(it2);
                L = min(L, l);
                R = max(R, r);
            }
            if (R - L <= X)
                return 0;
        }
        return 1;
    };
    cout << *ranges::partition_point(views::iota(0, inf), pred) << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

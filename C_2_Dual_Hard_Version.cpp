#define NDEBUG
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    vector<pair<int, int>> ans;
    auto act = [&](int i, int j) {
        assert(0 <= i && i < N);
        assert(0 <= j && j < N);
        A[i] += A[j];
        ans.emplace_back(i, j);
        assert(ans.size() <= 31);
    };
    auto a = 0, b = 0;
    for (auto i = 0; i < N; ++i) {
        if (0 < A[i]) {
            ++a;
        } else if (A[i] < 0) {
            ++b;
        }
    }
    auto pref = [&] {
        for (auto i = 0; i < N - 1; ++i) {
            act(i + 1, i);
        }
    };
    auto suff = [&] {
        for (auto i = N - 1; 0 < i; --i) {
            act(i - 1, i);
        }
    };
    if (b == 0) {
        pref();
    } else if (a == 0) {
        suff();
    } else {
        if (abs(ranges::min(A)) < abs(ranges::max(A))) {
            if (b <= 12) {
                auto it = ranges::max_element(A);
                auto p = int(it - A.begin());
                for (auto i = 0; i < N; ++i) {
                    if (A[i] < 0) {
                        act(i, p);
                    }
                }
                pref();
            } else {
                auto it = ranges::min_element(A);
                auto p = int(it - A.begin());
                for (auto i = 0; i < 5; ++i) {
                    act(p, p);
                }
                for (auto i = 0; i < N; ++i) {
                    if (0 < A[i]) {
                        act(i, p);
                    }
                }
                suff();
            }
        } else {
            if (a <= 12) {
                auto it = ranges::min_element(A);
                auto p = int(it - A.begin());
                for (auto i = 0; i < N; ++i) {
                    if (0 < A[i]) {
                        act(i, p);
                    }
                }
                suff();
            } else {
                auto it = ranges::max_element(A);
                auto p = int(it - A.begin());
                for (auto i = 0; i < 5; ++i) {
                    act(p, p);
                }
                for (auto i = 0; i < N; ++i) {
                    if (A[i] < 0) {
                        act(i, p);
                    }
                }
                pref();
            }
        }
    }
    assert(ranges::is_sorted(A));
    cout << ans.size() << "\n";
    for (auto [i, j] : ans) {
        cout << i + 1 << " " << j + 1 << "\n";
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

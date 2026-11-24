#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int mex(vector<int> A) {
    ranges::sort(A);
    A.erase(unique(begin(A), end(A)), end(A));
    auto N = int(A.size());
    for (auto i = 0; i < N; ++i) {
        if (A[i] != i) {
            return i;
        }
    }
    return N;
}

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    copy_n(istream_iterator<int>(cin), N, begin(A));
    auto cnt = ranges::count(A, 0);
    vector<pair<int, int>> ans;
    if (cnt == 0) {
        for (auto i = 0; i < N; ++i) {
            ans.emplace_back(i, i + 1);
        }
    } else if (cnt == 1) {
        cout << -1 << "\n";
        return;
    } else {
        auto X = mex(A);
        set<int> S;
        auto p = -1;
        for (auto i = 0; i < N; ++i) {
            if (A[i] < X) {
                S.insert(A[i]);
            }
            if (int(S.size()) == X) {
                p = i + 1;
                break;
            }
        }
        vector<int> B;
        for (auto i = p; i < N; ++i) {
            B.push_back(A[i]);
        }
        if (X == mex(B)) {
            ans.emplace_back(0, p);
            ans.emplace_back(p, N);
        } else {
            cout << -1 << "\n";
            return;
        }
    }
    cout << size(ans) << "\n";
    for (auto [l, r] : ans) {
        cout << l + 1 << " " << r << "\n";
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

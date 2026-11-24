#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

auto F(const vector<int> &A) {
    auto N = int(A.size());
    map<int, vector<int>> G;
    for (auto i = 0; i < N; ++i) {
        G[A[i]].push_back(i);
    }
    auto X = -1;
    for (const auto &[x, v] : G) {
        auto l = v.front();
        auto r = v.back();
        auto len = r - l + 1;
        if (int(v.size()) < len) {
            X = x;
            break;
        }
    }
    return pair(G, X);
}

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    copy_n(istream_iterator<int>(cin), N, begin(A));
    auto [G, X] = F(A);
    if (X == -1) {
        cout << "YES\n";
        return;
    }
    {
        auto B = A;
        auto L = G[X].front();
        auto R = G[X].back();
        for (auto i = L;; ++i) {
            if (B[i] != X) {
                swap(B[i], B[R]);
                break;
            }
        }
        if (F(B).second == -1) {
            cout << "YES\n";
            return;
        }
    }
    {
        auto B = A;
        auto L = G[X].front();
        auto R = G[X].back();
        for (auto i = R;; --i) {
            if (B[i] != X) {
                swap(B[L], B[i]);
                break;
            }
        }
        if (F(B).second == -1) {
            cout << "YES\n";
            return;
        }
    }
    {
        auto B = A;
        auto L = G[X].front();
        auto R = G[X].back();
        if (0 <= L - 1) {
            swap(B[L - 1], B[R]);
        }
        if (F(B).second == -1) {
            cout << "YES\n";
            return;
        }
    }
    {
        auto B = A;
        auto L = G[X].front();
        auto R = G[X].back();
        if (R + 1 < N) {
            swap(B[L], B[R + 1]);
        }
        if (F(B).second == -1) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

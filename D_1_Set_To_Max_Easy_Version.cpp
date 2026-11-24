#define NDEBUG
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void solve() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    for (auto i = 0; i < N; ++i) {
        cin >> B[i];
    }
    vector<pair<int, int>> P(N);
    for (auto i = 0; i < N; ++i) {
        P[i] = {B[i], i};
    }
    ranges::sort(P);
    vector<int> color(N);
    auto probe_left = [&](int x, int pos) {
        auto found = -1;
        for (auto i = pos; 0 <= i; --i) {
            if (x < A[i] || (B[i] < x && color[i])) {
                return false;
            }
            if (A[i] == x) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            return false;
        }
        return true;
    };
    auto probe_right = [&](int x, int pos) {
        auto found = -1;
        for (auto i = pos; i < N; ++i) {
            if (x < A[i] || (B[i] < x && color[i])) {
                return false;
            }
            if (A[i] == x) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            return false;
        }
        return true;
    };
    for (auto [x, pos] : P) {
        auto ok = probe_left(x, pos) || probe_right(x, pos);
        if (!ok) {
            cout << "NO\n";
            return;
        }
        color[pos] = 1;
    }
    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

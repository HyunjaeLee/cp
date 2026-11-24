#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

template <typename T> void read(vector<T> &a) {
    auto n = int(a.size());
    for (auto i = 0; i < n; ++i) {
        cin >> a[i];
    }
}

template <typename T> void show(const vector<T> &a) {
    auto n = int(a.size());
    for (auto i = 0; i < n; ++i) {
        cout << a[i] << (i < n - 1 ? " " : "\n");
    }
}

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    read(A);
    auto sum = accumulate(begin(A), end(A), 0LL);
    if (sum % N != 0) {
        cout << "No\n";
        return;
    }
    auto avg = sum / N;
    vector<int> G(60), pos(60), neg(60);
    vector<pair<int, int>> nodes;
    for (auto i = 0; i < N; ++i) {
        auto delta = avg - A[i];
        if (delta == 0)
            continue;
        auto a = 1LL << (__lg(abs(delta)) + 1);
        auto b = 1LL << countr_zero(u64(abs(delta)));
        if (abs(delta) != a - b) {
            cout << "No\n";
            return;
        }
        if (popcount(u64(abs(delta))) == 1) {
            if (0 < delta) {
                pos[b] += 1;
            } else {
                neg[b] += 1;
            }
        }
        if (delta < 0) {
            swap(a, b);
        }
        G[__lg(a)]++;
        G[__lg(b)]--;
    }
    for (auto i = 59; 0 < i; --i) {
        if (0 < G[i]) {
            pos[i - 1] -= G[i];
            G[i] = 0;
        } else if (G[i] < 0) {
            neg[i - 1] += G[i];
            G[i] = 0;
        }
    }
    for (auto i = 59; 0 <= i; --i) {
        if (G[i] != 0 || (0 < i && (pos[i - 1] < 0 || neg[i - 1] < 0))) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    cin >> t;
    for (auto i = 0; i < t; ++i)
        solve();
}

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

int query(int i) {
    cout << "? " << i + 1 << endl;
    char c;
    cin >> c;
    if (c == '>') {
        return 1;
    } else if (c == '<') {
        return -1;
    } else {
        return 0;
    }
}

void answer(const vector<int> &A) {
    auto N = int(A.size());
    cout << "! ";
    for (auto i = 0; i < N; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void solve() {
    int N;
    cin >> N;
    int idx1, idxN, X;
    {
        auto idx = 0;
        auto delta = 0;
        for (auto i = 0; i < N; ++i) {
            int r;
            while ((r = query(i)) < 0) {
                delta -= 1;
            }
            if (r == 0) {
                idx = i;
            } else {
                delta += 1 + query(idx);
            }
        }
        idx1 = idx;
        X = 1 - delta;
    }
    {
        auto idx = 0;
        for (auto i = 0; i < N; ++i) {
            int r;
            while (0 < (r = query(i)))
                ;
            if (r == 0) {
                idx = i;
            } else {
                query(idx);
            }
        }
        idxN = idx;
    }
    auto Val = N;
    auto Set = [&](int x) {
        if (x < Val) {
            for (auto i = 0; i < Val - x; ++i) {
                query(idx1);
            }
        } else if (Val < x) {
            for (auto i = 0; i < x - Val; ++i) {
                query(idxN);
            }
        }
        Val = x;
    };
    vector<int> A(N);
    auto F = [&](auto &&self, int l, int r, vector<int> v) -> void {
        if (v.empty())
            return;
        auto mid = l + (r - l) / 2;
        Set(mid);
        vector<int> L, R;
        for (auto i : v) {
            auto res = query(i);
            if (res < 0) {
                L.push_back(i);
                query(idxN);
            } else if (0 < res) {
                R.push_back(i);
                query(idx1);
            } else {
                A[i] = mid;
            }
        }
        self(self, l, mid - 1, L);
        self(self, mid + 1, r, R);
    };
    vector<int> V(N);
    ranges::iota(V, 0);
    F(F, 1, N, V);
    answer(A);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

void show(const vector<vector<int>> &A) {
    for (const auto &row : A) {
        for (auto x : row) {
            cout << x << " ";
        }
        cout << "\n";
    }
}

void solve() {
    int N, R, C;
    cin >> N >> R >> C;
    --R, --C;
    vector<vector<int>> A(N, vector<int>(N));
    auto scan1 = [&](int r1, int c1, int r2, int c2) -> bool {
        for (auto r = r1; r <= r2; ++r) {
            if (pair{r, c1} == pair{R, C})
                return false;
        }
        for (auto c = c1; c <= c2; ++c) {
            if (pair{r1, c} == pair{R, C})
                return false;
        }
        return true;
    };
    auto scan2 = [&](int r1, int c1, int r2, int c2) -> bool {
        for (auto r = r1; r <= r2; ++r) {
            if (pair{r, c2} == pair{R, C})
                return false;
        }
        for (auto c = c1; c <= c2; ++c) {
            if (pair{r1, c} == pair{R, C})
                return false;
        }
        return true;
    };
    auto scan3 = [&](int r1, int c1, int r2, int c2) -> bool {
        for (auto r = r1; r <= r2; ++r) {
            if (pair{r, c1} == pair{R, C})
                return false;
        }
        for (auto c = c1; c <= c2; ++c) {
            if (pair{r2, c} == pair{R, C})
                return false;
        }
        return true;
    };
    auto scan4 = [&](int r1, int c1, int r2, int c2) -> bool {
        for (auto r = r1; r <= r2; ++r) {
            if (pair{r, c2} == pair{R, C})
                return false;
        }
        for (auto c = c1; c <= c2; ++c) {
            if (pair{r2, c} == pair{R, C})
                return false;
        }
        return true;
    };
    auto color1 = [&](int r1, int c1, int r2, int c2) -> bool {
        for (auto r = r1; r <= r2; ++r) {
            A[r][c1] = r2 - r1;
        }
        for (auto c = c1; c <= c2; ++c) {
            A[r1][c] = r2 - r1;
        }
        return true;
    };
    auto color2 = [&](int r1, int c1, int r2, int c2) -> bool {
        for (auto r = r1; r <= r2; ++r) {
            A[r][c2] = r2 - r1;
        }
        for (auto c = c1; c <= c2; ++c) {
            A[r1][c] = r2 - r1;
        }
        return true;
    };
    auto color3 = [&](int r1, int c1, int r2, int c2) -> bool {
        for (auto r = r1; r <= r2; ++r) {
            A[r][c1] = r2 - r1;
        }
        for (auto c = c1; c <= c2; ++c) {
            A[r2][c] = r2 - r1;
        }
        return true;
    };
    auto color4 = [&](int r1, int c1, int r2, int c2) -> bool {
        for (auto r = r1; r <= r2; ++r) {
            A[r][c2] = r2 - r1;
        }
        for (auto c = c1; c <= c2; ++c) {
            A[r2][c] = r2 - r1;
        }
        return true;
    };
    [&](this auto &&self, int r1, int c1, int r2, int c2) -> void {
        if (r1 == r2)
            return;
        if (scan1(r1, c1, r2, c2)) {
            color1(r1, c1, r2, c2);
            self(r1 + 1, c1 + 1, r2, c2);
        } else if (scan2(r1, c1, r2, c2)) {
            color2(r1, c1, r2, c2);
            self(r1 + 1, c1, r2, c2 - 1);
        } else if (scan3(r1, c1, r2, c2)) {
            color3(r1, c1, r2, c2);
            self(r1, c1 + 1, r2 - 1, c2);
        } else if (scan4(r1, c1, r2, c2)) {
            color4(r1, c1, r2, c2);
            self(r1, c1, r2 - 1, c2 - 1);
        }
    }(0, 0, N - 1, N - 1);
    show(A);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

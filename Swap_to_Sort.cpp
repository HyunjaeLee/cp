#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
}
// clang-format on

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    for (auto i = 0; i < N; ++i) {
        --A[i];
    }
    auto Find = [&](int f) {
        for (auto i = 0; i < N; ++i) {
            if ((A[i] & 1) == f && (i & 1) != f) {
                return i;
            }
        }
        return -1;
    };
    vector<pair<char, int>> ans;
    auto Swap = [&](int i, int j) {
        assert(0 <= i && i < N);
        assert(0 <= j && j < N);
        assert(abs(i - j) == 1 || abs(i - j) == 2);
        if (i > j)
            swap(i, j);
        swap(A[i], A[j]);
        if (abs(i - j) == 1) {
            ans.emplace_back('A', i + 1);
        } else {
            ans.emplace_back('B', i + 1);
        }
    };
    for (auto i = Find(0), j = Find(1); i != -1 && j != -1; i = Find(0), j = Find(1)) {
        if (i > j)
            swap(i, j);
        while (j - i > 1) {
            Swap(i, i + 2);
            i += 2;
        }
        assert(j == i + 1);
        Swap(i, i + 1);
    }
    // assert(Find(0) == -1);
    // assert(Find(1) == -1);
    // 버블소트 실수함 ㅋㅋㅋ...
    for (auto f = 0; f < 2; ++f) {
        for (auto i = f; i < N; i += 2) {
            for (auto j = f; j + 2 < N; j += 2) {
                if (A[j] > A[j + 2]) {
                    Swap(j, j + 2);
                }
            }
        }
    }
    assert(ans.size() <= 100000);
    assert(ranges::is_sorted(A));
    cout << size(ans) << "\n";
    for (auto [op, i] : ans) {
        cout << op << " " << i << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}

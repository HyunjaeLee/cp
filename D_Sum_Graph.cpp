#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

#define TC
void solve() {
    int N;
    cin >> N;
    auto Add = [&](int x) {
        cout << "+ " << x << endl;
        int r;
        cin >> r;
        if (r == -2)
            exit(0);
        return r;
    };
    auto Ask = [&](int i, int j) {
        cout << "? " << i << " " << j << endl;
        int r;
        cin >> r;
        assert(r != -1);
        if (r == -2)
            exit(0);
        return r;
    };
    Add(N + 1);
    Add(N + 2);
    auto far = pair(-1, -1); // (dist, id)
    for (auto i = 2; i <= N; ++i) {
        far = max(far, pair(Ask(1, i), i));
    }
    auto root = far.second;
    vector<int> A(N);
    A[0] = root;
    for (auto i = 1; i <= N; ++i) {
        if (i == root)
            continue;
        A[Ask(root, i)] = i;
    }
    deque<int> dq;
    for (auto i = 0; i < N; ++i) {
        dq.push_back(i);
    }
    vector<int> order;
    while (!dq.empty()) {
        order.push_back(dq.front());
        dq.pop_front();
        if (!dq.empty()) {
            order.push_back(dq.back());
            dq.pop_back();
        }
    }
    vector<int> ans1(N), ans2(N);
    for (auto [i, x] : views::zip(order, A)) {
        ans1[x - 1] = i + 1;
    }
    for (auto [i, x] : views::zip(order | views::reverse, A)) {
        ans2[x - 1] = i + 1;
    }
    cout << "!";
    for (auto x : ans1) {
        cout << " " << x;
    }
    for (auto x : ans2) {
        cout << " " << x;
    }
    cout << endl;
    int r;
    cin >> r;
    if (r == -2)
        exit(0);
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

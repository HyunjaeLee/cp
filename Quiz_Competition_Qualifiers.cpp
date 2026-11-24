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

struct node {
    explicit node(int x = 0) : val(x), next{0, 0} {}
    ~node() {
        delete next[0];
        delete next[1];
    }
    int val;
    array<node *, 2> next;
};

void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    string T;
    cin >> T;
    vector<string> S(N);
    read(S);
    vector<vector<int>> A(N, vector<int>(K));
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < K; ++j) {
            A[i][j] = int(S[i][j] == T[j]);
        }
    }
    node *root = new node(0);
    auto Insert = [&](const vector<int> &a, int w) {
        auto u = root;
        for (auto i = 0; i < K; ++i) {
            auto &v = u->next[a[i]];
            if (v) {
                v->val += w;
            } else {
                v = new node(w);
            }
            u = v;
        }
    };
    for (auto i = 0; i < N; ++i) {
        Insert(A[i], 1);
    }
    auto check = [&](int e) {
        auto good = 0;
        auto p = root;
        for (auto i = 0; i < K; ++i) {
            auto c = p->next[1] ? p->next[1]->val : 0;
            if (c + good <= M) { // qualified
                good += c;
                if (A[e][i] == 1)
                    return true;
                if (!p->next[0]) {
                    p->next[0] = new node(0);
                }
                p = p->next[0];
            } else {
                if (A[e][i] == 0)
                    return false;
                if (!p->next[1]) {
                    p->next[1] = new node(0);
                }
                p = p->next[1];
            }
        }
        return false;
    };
    int Q;
    cin >> Q;
    while (Q--) {
        int i, j;
        cin >> i >> j;
        --i, --j;
        Insert(A[i], -1);
        A[i][j] ^= 1;
        Insert(A[i], 1);
        cout << (check(i) ? "Yes\n" : "No\n");
    }
    delete root;
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

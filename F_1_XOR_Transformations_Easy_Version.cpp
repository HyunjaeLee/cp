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

template <class Int, class Count = int> struct BinaryTrie {
    int maxD;
    std::vector<Count> deg, subtree_sum;
    std::vector<int> ch0, ch1, par;

    int _new_node(int id_par) {
        deg.emplace_back(Count());
        subtree_sum.emplace_back(Count());
        ch0.emplace_back(-1);
        ch1.emplace_back(-1);
        par.emplace_back(id_par);
        return (int)ch0.size() - 1;
    }

    BinaryTrie(int maxD_ = 0) : maxD(maxD_) { _new_node(-1); }

    // Return index of x.
    // Create nodes to locate x if needed.
    int _get_create_index(Int x) {
        int now = 0;
        for (int d = maxD - 1; d >= 0; --d) {
            int nxt = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (nxt == -1) {
                nxt = _new_node(now);
                (((x >> d) & 1) ? ch1[now] : ch0[now]) = nxt;
            }
            now = nxt;
        }
        return now;
    }

    // Return node index of x.
    // Return -1 if x is not in trie.
    int _get_index(Int x) const {
        int now = 0;
        for (int d = maxD - 1; d >= 0; --d) {
            now = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (now == -1)
                return -1;
        }
        return now;
    }

    // insert x
    void insert(Int x, Count c = Count(1)) {
        int now = _get_create_index(x);
        deg[now] += c;
        while (now >= 0)
            subtree_sum[now] += c, now = par[now];
    }

    // delete x if exists
    void erase(Int x) {
        int now = _get_index(x);
        if (now >= 0 and deg[now] != 0) {
            Count r = deg[now];
            deg[now] = 0;
            while (now >= 0)
                subtree_sum[now] -= r, now = par[now];
        }
    }

    Count count(Int x) const {
        int now = _get_index(x);
        return now == -1 ? Count() : deg[now];
    }

    bool contains(Int x) const { return count(x) > Count(); }

    // min(y ^ x) for y in trie
    Int xor_min(Int x) const {
        Int ret = 0;
        int now = 0;
        if (!subtree_sum[now])
            return -1;
        for (int d = maxD - 1; d >= 0; d--) {
            int y = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (y != -1 and subtree_sum[y]) {
                now = y;
            } else {
                ret += Int(1) << d, now = ch0[now] ^ ch1[now] ^ y;
            }
        }
        return ret;
    }

    // Count elements y such that x ^ y < thres
    Count count_less_xor(Int x, Int thres) const {
        if (thres <= 0)
            return Count();
        if ((thres >> maxD) > 0)
            return subtree_sum[0];
        Count ret = Count();
        int now = 0;

        for (int d = maxD - 1; d >= 0; d--) {
            if (now == -1)
                break;

            const bool bit_x = (x >> d) & 1;

            if ((thres >> d) & 1) {
                const int child = bit_x ? ch1[now] : ch0[now];
                if (child != -1)
                    ret += subtree_sum[child];

                now = bit_x ? ch0[now] : ch1[now];
            } else {
                now = bit_x ? ch1[now] : ch0[now];
            }
        }

        return ret;
    }
};

#define TC
void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    read(A);
    ranges::sort(A);
    vector<vector<int>> V{A};
    auto G = [&](vector<int> a) {
        vector<int> b;
        vector<int> v;
        BinaryTrie<int> trie(30);
        for (auto i = 1; i < N; ++i) {
            trie.insert(a[i - 1]);
            auto x = trie.xor_min(a[i]);
            assert(x != -1);
            v.push_back(x);
            auto y = a[i] ^ x;
            trie.erase(y);
            auto z = trie.xor_min(a[i]);
            if (z != -1)
                v.push_back(z);
            trie.insert(y);
        }
        ranges::sort(v);
        v.erase(unique(begin(v), end(v)), end(v));
        for (auto x : v) {
            map<int, int> mp;
            for (auto i = 0; i < N; ++i) {
                auto c = mp[a[i] ^ x];
                for (auto k = 0; k < c; ++k) {
                    b.push_back(x);
                    if (ssize(b) == N) {
                        return b;
                    }
                }
                ++mp[a[i]];
            }
        }
        assert(0);
    };
    while (0 < V.back()[N - 1]) {
        V.push_back(G(V.back()));
    }
    auto K = int(V.size());
    vector<int> ans(K);
    for (auto i = 0; i < K; ++i) {
        ans[i] = ranges::max(V[i]) - ranges::min(V[i]);
    }
    while (Q--) {
        int x;
        cin >> x;
        cout << (K <= x ? 0 : ans[x]) << "\n";
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

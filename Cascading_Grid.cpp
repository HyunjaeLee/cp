#include <atcoder/dsu>
#include <atcoder/maxflow>
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

template <typename T, bool minimize = true> struct BurnBury {
private:
    using MaxFlow = atcoder::mf_graph<T>;
    using UF = atcoder::dsu;
    using arr2 = std::array<T, 2>;
    using arr4 = std::array<T, 4>;

    int n;
    T alpha;
    std::vector<arr2> theta;
    std::vector<std::map<int, arr4>> phi;
    std::map<std::vector<int>, T> zeta;

public:
    explicit BurnBury(int n_) : n{n_}, alpha{}, theta(n), phi(n) {}

    void add_cost(T cost) {
        if (not minimize)
            cost *= -1;
        alpha += cost;
    }

    void add_cost(int x, T cost) {
        if (not minimize)
            cost *= -1;
        int a = std::max(~x, x);
        theta[a][x >= 0] += cost;
    }

    void add_cost(int x, int y, T cost) {
        assert(x != y);
        if (not minimize)
            cost *= -1;
        int a = std::max(~x, x), b = std::max(~y, y);
        if (a < b)
            phi[a][b][((x >= 0) << 1) | (y >= 0)] += cost;
        else
            phi[b][a][((y >= 0) << 1) | (x >= 0)] += cost;
    }

    void add_cost(std::vector<int> xs, T cost) {
        assert(not xs.empty());
        if (xs.size() == 1) {
            add_cost(xs[0], cost);
        } else if (xs.size() == 2) {
            add_cost(xs[0], xs[1], cost);
        } else {
            int m = (int)xs.size();
            std::sort(xs.begin(), xs.end());
            xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
            assert(m == (int)xs.size());
            if (not minimize)
                cost *= -1;
            zeta[xs] += cost;
        }
    }

    std::optional<std::pair<T, std::vector<bool>>> solve() {
        std::vector<int> flip(2 * n, -1);
        {
            UF uf(n + n);
            for (int i = 0; i < n; i++) {
                for (auto &[j, cs] : phi[i]) {
                    T c = -cs[0] + cs[1] + cs[2] - cs[3];
                    if (c < 0) {
                        uf.merge(i, j + n);
                        uf.merge(i + n, j);
                    }
                    if (c > 0) {
                        uf.merge(i, j);
                        uf.merge(i + n, j + n);
                    }
                }
            }
            for (auto &[vs, c] : zeta) {
                if (c > 0)
                    return std::nullopt;
                if (c < 0) {
                    for (int i = 1; i < (int)vs.size(); i++) {
                        int x = vs[i - 1], y = vs[i];
                        int a = std::max(x, ~x), b = std::max(y, ~y);
                        if ((x >= 0) ^ (y >= 0)) {
                            uf.merge(a, b + n);
                            uf.merge(a + n, b);
                        } else {
                            uf.merge(a, b);
                            uf.merge(a + n, b + n);
                        }
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                int x = uf.leader(i);
                int y = uf.leader(i + n);
                if (x == y)
                    return std::nullopt;
                if (flip[x] < 0) {
                    flip[x] = 0;
                    flip[y] = 1;
                }
            }
            for (int i = 0; i < n; i++) {
                if (flip[i] < 0) {
                    flip[i] = flip[uf.leader(i)];
                }
            }
            flip.resize(n);
        }
        {
            for (int i = 0; i < n; i++) {
                for (auto &[j, cs] : phi[i]) {
                    if (flip[i]) {
                        std::swap(cs[0], cs[2]);
                        std::swap(cs[1], cs[3]);
                    }
                    if (flip[j]) {
                        std::swap(cs[0], cs[1]);
                        std::swap(cs[2], cs[3]);
                    }
                    T c = -cs[0] + cs[1] + cs[2] - cs[3];
                    alpha += cs[0];
                    theta[i][not flip[i]] += cs[2] - cs[0];
                    theta[j][not flip[j]] += cs[3] - cs[2];
                    cs[1] = c;
                    cs[0] = cs[2] = cs[3] = 0;
                }
            }
        }
        {
            for (int i = 0; i < n; i++) {
                auto &cs = theta[i];
                if (flip[i]) {
                    std::swap(cs[0], cs[1]);
                }
                if (cs[0] <= cs[1]) {
                    alpha += cs[0];
                    cs[1] -= cs[0];
                    cs[0] = 0;
                } else {
                    alpha += cs[1];
                    cs[0] -= cs[1];
                    cs[1] = 0;
                }
            }
        }

        MaxFlow flow(n + 2 + int(zeta.size()));
        int s = n, t = n + 1;
        {
            for (int i = 0; i < n; i++) {
                auto &cs = theta[i];
                if (cs[1] > 0) {
                    flow.add_edge(i, t, cs[1]);
                }
                if (cs[0] > 0) {
                    flow.add_edge(s, i, cs[0]);
                }
            }
            for (int i = 0; i < n; i++) {
                for (auto &[j, cs] : phi[i]) {
                    if (cs[2] > 0) {
                        flow.add_edge(i, j, cs[2]);
                    }
                    if (cs[1] > 0) {
                        flow.add_edge(j, i, cs[1]);
                    }
                }
            }
            int u = t + 1;
            for (auto &[vs, c] : zeta) {
                if (c < 0) {
                    if ((vs[0] >= 0) ^ flip[std::max(~vs[0], vs[0])]) {
                        flow.add_edge(s, u, -c);
                        for (auto &p : vs)
                            flow.add_edge(u, std::max(p, ~p), -c);
                    } else {
                        for (auto &p : vs)
                            flow.add_edge(std::max(p, ~p), u, -c);
                        flow.add_edge(u, t, -c);
                    }
                    alpha += c;
                    u++;
                }
            }
        }
        T ans = flow.flow(s, t) + alpha;
        std::vector<bool> cut = flow.min_cut(s);
        for (int i = 0; i < n; i++) {
            if (flip[i])
                cut[i] = 1 - cut[i];
        }
        cut.resize(n);
        return std::make_pair(minimize ? ans : -ans, cut);
    }
};

void solve() {
    int N, M;
    cin >> N >> M;
    vector<string> A(N);
    read(A);
    BurnBury<i64, false> bb(N * M);
    constexpr auto inf = numeric_limits<int>::max() / 2;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M; ++j) {
            auto x = i * M + j;
            if (A[i][j] == '+') {
                bb.add_cost(x, 1);
            } else if (A[i][j] == '-') {
                bb.add_cost(x, -1);
            }
        }
    }
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < M - 1; ++j) {
            auto x = i * M + j;
            auto y = i * M + j + 1;
            if (A[i][j] != '#' && A[i][j + 1] != '#') {
                bb.add_cost(x, ~y, -inf);
                bb.add_cost(~x, y, -inf);
            }
        }
    }
    for (auto i = 0; i < N - 1; ++i) {
        for (auto j = 0; j < M; ++j) {
            auto x = i * M + j;
            auto y = (i + 1) * M + j;
            if (A[i][j] != '#' && A[i + 1][j] != '#') {
                bb.add_cost(~x, y, -inf);
            }
        }
    }
    auto o = bb.solve();
    assert(o);
    auto ans = o->first;
    cout << ans << "\n";
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

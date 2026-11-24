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
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
}
// clang-format on

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

template <class Cap>
struct BKMaxFlow {
    using Traits = boost::adjacency_list_traits<
        boost::vecS,
        boost::vecS,
        boost::directedS
    >;

    using Edge = typename Traits::edge_descriptor;

    using VertexProperty =
        boost::property<
            boost::vertex_color_t,
            boost::default_color_type,
            boost::property<
                boost::vertex_distance_t,
                long,
                boost::property<
                    boost::vertex_predecessor_t,
                    Edge
                >
            >
        >;

    using EdgeProperty =
        boost::property<
            boost::edge_capacity_t,
            Cap,
            boost::property<
                boost::edge_residual_capacity_t,
                Cap,
                boost::property<
                    boost::edge_reverse_t,
                    Edge
                >
            >
        >;

    using Graph = boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::directedS,
        VertexProperty,
        EdgeProperty
    >;

    Graph g;

    explicit BKMaxFlow(int n) : g(n) {}

    void add_edge(int u, int v, Cap c) {
        auto cap = boost::get(boost::edge_capacity, g);
        auto res = boost::get(boost::edge_residual_capacity, g);
        auto rev = boost::get(boost::edge_reverse, g);

        auto [e, ok1] = boost::add_edge(u, v, g);
        auto [r, ok2] = boost::add_edge(v, u, g);

        assert(ok1 && ok2);

        cap[e] = c;
        cap[r] = 0;

        res[e] = c;
        res[r] = 0;

        rev[e] = r;
        rev[r] = e;
    }

    Cap flow(int s, int t) {
        return boost::push_relabel_max_flow(g, s, t);
    }

    std::vector<bool> min_cut(int s) {
        // ACL mf_graph::min_cut(s)와 같은 의미:
        // residual graph에서 s로부터 도달 가능한 정점.
        auto res = boost::get(boost::edge_residual_capacity, g);

        const int n = boost::num_vertices(g);

        std::vector<bool> vis(n);
        std::queue<int> q;

        vis[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            auto [it, last] = boost::out_edges(u, g);

            for (; it != last; ++it) {
                if (res[*it] <= 0) continue;

                int v = boost::target(*it, g);

                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }

        return vis;
    }
};

#include <atcoder/dsu>
#include <atcoder/maxflow>

// https://ei1333.github.io/library/graph/flow/burn-bury.hpp.html
enum class BurnBuryModel {
    Directed,
    Auxiliary,
};

template <typename T, bool minimize = true,
          BurnBuryModel model = BurnBuryModel::Directed>
struct BurnBury {
    explicit BurnBury(int N) : n{N}, alpha{}, theta(n), phi(n) {}

    void add_cost(T cost) {
        if (not minimize) cost *= -1;
        alpha += cost;
    }

    void add_cost(int x, T cost) {
        if (not minimize) cost *= -1;
        int a = std::max(~x, x);
        theta[a][x >= 0] += cost;
    }

    void add_cost(int x, int y, T cost) {
        assert(x != y);
        if (not minimize) cost *= -1;
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

            if (not minimize) cost *= -1;
            zeta[xs] += cost;
        }
    }

    std::optional<std::pair<T, std::vector<bool>>> solve() {
        std::vector<int> flip(2 * n, -1);

        // auxiliary backend에서 추가될 binary gadget
        std::vector<std::tuple<int, int, T>> binary_aux;

        // 1. 각 변수의 flip을 결정
        {
            atcoder::dsu uf(n + n);

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
                if (c > 0) return std::nullopt;

                if (c < 0) {
                    for (int i = 1; i < (int)vs.size(); i++) {
                        int x = vs[i - 1], y = vs[i];
                        int a = std::max(x, ~x);
                        int b = std::max(y, ~y);

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

                if (x == y) return std::nullopt;

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

        // 2. binary term을 graph-representable form으로 분해
        {
            for (int i = 0; i < n; i++) {
                for (auto &[j, cs] : phi[i]) {
                    // transformed variables 기준으로 table transpose
                    if (flip[i]) {
                        std::swap(cs[0], cs[2]);
                        std::swap(cs[1], cs[3]);
                    }
                    if (flip[j]) {
                        std::swap(cs[0], cs[1]);
                        std::swap(cs[2], cs[3]);
                    }

                    const T A = cs[0];
                    const T B = cs[1];
                    const T C = cs[2];
                    const T D = cs[3];

                    const T c = B + C - A - D;
                    assert(c >= 0);

                    if constexpr (model == BurnBuryModel::Directed) {
                        // 기존 ei1333 모델:
                        //
                        // f =
                        //   A
                        // + (C-A)x
                        // + (D-C)y
                        // + c [x=0,y=1]

                        alpha += A;
                        theta[i][not flip[i]] += C - A;
                        theta[j][not flip[j]] += D - C;

                        cs[1] = c;
                        cs[0] = cs[2] = cs[3] = 0;

                    } else {
                        // auxiliary 모델:
                        //
                        // f =
                        //   A
                        // + (C-A)x
                        // + (B-A)y
                        // - cxy
                        //
                        // -cxy =
                        //   -c + min_aux {
                        //       c [aux=0]
                        //     + c [aux=1,x=0]
                        //     + c [aux=1,y=0]
                        //   }

                        alpha += A - c;

                        theta[i][not flip[i]] += C - A;
                        theta[j][not flip[j]] += B - A;

                        if (c > 0) {
                            binary_aux.emplace_back(i, j, c);
                        }
                    }
                }
            }
        }

        // 3. unary normalize
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

        const int extra =
            int(zeta.size()) +
            (model == BurnBuryModel::Auxiliary
                 ? int(binary_aux.size())
                 : 0);

        BKMaxFlow<T> flow(n + 2 + extra);

        const int s = n;
        const int t = n + 1;

        // 4. unary
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
        }

        int u = t + 1;

        // 5. binary
        if constexpr (model == BurnBuryModel::Directed) {
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
        } else {
            for (auto [x, y, c] : binary_aux) {
                // cost:
                //   c if aux = false
                //   c if aux = true, x = false
                //   c if aux = true, y = false
                //
                // alpha에 이미 -c가 들어가 있다.
                flow.add_edge(s, u, c);
                flow.add_edge(u, x, c);
                flow.add_edge(u, y, c);
                ++u;
            }
        }

        // 6. 기존 higher-order zeta
        {
            for (auto &[vs, c] : zeta) {
                if (c < 0) {
                    if ((vs[0] >= 0) ^
                        flip[std::max(~vs[0], vs[0])]) {

                        flow.add_edge(s, u, -c);

                        for (auto &p : vs) {
                            flow.add_edge(
                                u, std::max(p, ~p), -c);
                        }
                    } else {
                        for (auto &p : vs) {
                            flow.add_edge(
                                std::max(p, ~p), u, -c);
                        }

                        flow.add_edge(u, t, -c);
                    }

                    alpha += c;
                    ++u;
                }
            }
        }

        T ans = flow.flow(s, t) + alpha;

        std::vector<bool> cut = flow.min_cut(s);

        for (int i = 0; i < n; i++) {
            if (flip[i]) {
                cut[i] = 1 - cut[i];
            }
        }

        cut.resize(n);

        return std::pair(
            minimize ? ans : -ans,
            cut
        );
    }

private:
    int n;
    T alpha;

    std::vector<std::array<T, 2>> theta;
    std::vector<std::map<int, std::array<T, 4>>> phi;
    std::map<std::vector<int>, T> zeta;
};

#define TC
void solve() {
    int N, D;
    cin >> N >> D;
    vector<pair<int, int>> E(N * D);
    for (auto &[u, v] : E) {
        cin >> u >> v;
        --u, --v;
    }
    // if (N == 1) {
    //     cout << "Yes\n";
    //     return;
    // }
    // for (auto i = 0; i < N; ++i) {
    //     if (deg[i] <= D) {
    //         cout << "No\n";
    //         return;
    //     }
    // }
    // if (D == 1) {
    //     atcoder::dsu uf(N);
    //     for (auto [u, v] : E) {
    //         uf.merge(u, v);
    //     }
    //     cout << (uf.size(0) == N ? "Yes\n" : "No\n");
    //     return;
    // }
    // mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> I(N);
    ranges::iota(I, 0);
    // ranges::shuffle(I, rng);
    constexpr auto inf = numeric_limits<int>::max() / 2;
    { // x_0 = 1; avoid x = 111...11
        BurnBury<i64, false, BurnBuryModel::Auxiliary> bb(N);
        for (auto i = 0; i < N; ++i) {
            bb.add_cost(I[i], (-D * (N + 1)) - 1);
        }
        for (auto [u, v] : E) {
            bb.add_cost(I[u], I[v], 1 * (N + 1));
        }
        bb.add_cost(~I[0], -inf);
        bb.add_cost(I[0], N);
        auto res = bb.solve();
        assert(res);
        auto [f, x] = *res;
        auto cnt = ranges::count(x, true);
        if (cnt < N) {
            cout << "No\n";
            return;
        }
    }
    { // x_0 = 0; avoid x = 000...00
        BurnBury<i64, false, BurnBuryModel::Auxiliary> bb(N);
        for (auto i = 0; i < N; ++i) {
            bb.add_cost(I[i], (-D * (N + 1)) + 1);
        }
        for (auto [u, v] : E) {
            bb.add_cost(I[u], I[v], 1 * (N + 1));
        }
        bb.add_cost(I[0], -inf);
        auto res = bb.solve();
        assert(res);
        auto [f, x] = *res;
        auto cnt = ranges::count(x, true);
        if (0 < cnt) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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

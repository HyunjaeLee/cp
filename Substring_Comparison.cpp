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

struct Edge {
    int from, to, weight;
};

class NegativeCycleEdges {
    int n, m;
    const vector<Edge>& edges;
    vector<vector<int>> adj;

    vector<char> banned, answer;
    string bannedKey;
    unordered_set<string> visited;

    // SPFA로 음수 사이클 하나를 찾아 간선 ID 반환
    // 없으면 빈 벡터 반환
    vector<int> findOneNegativeCycle() const {
        vector<long long> dist(n, 0);
        vector<int> parentEdge(n, -1);
        vector<char> inQueue(n, 1);

        queue<int> q;
        for (int v = 0; v < n; ++v)
            q.push(v);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = 0;

            for (int id : adj[u]) {
                if (banned[id]) continue;

                const auto& e = edges[id];
                int v = e.to;

                long long nd = dist[u] + (long long)e.weight;
                if (nd >= dist[v]) continue;

                dist[v] = nd;
                parentEdge[v] = id;

                // predecessor 그래프에서 사이클 확인
                int x = v;

                for (int step = 0;
                     step < n && parentEdge[x] != -1;
                     ++step) {
                    x = edges[parentEdge[x]].from;
                    if (x == v) break;
                }

                if (x == v) {
                    vector<int> cycle;
                    int cur = v;

                    do {
                        int pe = parentEdge[cur];
                        cycle.push_back(pe);
                        cur = edges[pe].from;
                    } while (cur != v);

                    return cycle;
                }

                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = 1;
                }
            }
        }

        return {};
    }

    // 간선 제외 분기 탐색
    void dfs() {
        // 동일한 제외 상태 중복 탐색 방지
        if (!visited.insert(bannedKey).second)
            return;

        vector<int> cycle = findOneNegativeCycle();

        if (cycle.empty()) return;

        // 현재 발견한 사이클의 간선 기록
        for (int id : cycle)
            answer[id] = 1;

        // 다른 음수 사이클은 현재 사이클의
        // 간선 중 적어도 하나를 사용하지 않음
        for (int id : cycle) {
            banned[id] = 1;
            bannedKey[id] = '1';

            dfs();

            bannedKey[id] = '0';
            banned[id] = 0;
        }
    }

public:
    NegativeCycleEdges(int n_, const vector<Edge>& es)
        : n(n_), m((int)es.size()), edges(es),
          adj(n_), banned(m, 0), answer(m, 0),
          bannedKey(m, '0') {

        for (int id = 0; id < m; ++id)
            adj[edges[id].from].push_back(id);
    }

    vector<int> solve() {
        dfs();

        vector<int> ids;
        for (int id = 0; id < m; ++id) {
            if (answer[id])
                ids.push_back(id);
        }
        return ids;
    }
};

vector<tuple<int, int, int>> allNegativeCycleEdges(
    int n, const vector<Edge>& edges
) {
    auto ids = NegativeCycleEdges(n, edges).solve();

    vector<tuple<int, int, int>> result;
    result.reserve(ids.size());

    for (int id : ids) {
        const auto& e = edges[id];
        result.emplace_back(e.from, e.to, e.weight);
    }

    return result;
}


void solve() {
    int N, M;
    cin >> N >> M;
    constexpr auto inf = numeric_limits<int>::max() / 2;
    vector<array<int, 4>> A(M);
    for (auto &[a, b, c, d] : A) {
        cin >> a >> b >> c >> d;
        --a, --b, --c, --d;
    }
    vector<vector<int>> G(N, vector<int>(N, inf));
    for (auto [a, b, c, d] : A) {
        G[a][c] = -1;
    }
    vector<int> right(M);
    while (true) {
        vector<Edge> E;
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < N; ++j) {
                if (G[i][j] < inf) {
                    E.push_back({i, j, G[i][j]});
                }
            }
        }
        auto edges = allNegativeCycleEdges(N, E);
        if (edges.empty()) {
            break;
        }
        ranges::sort(edges);
        vector<bool> hot(M);
        for (auto i = 0; i < M; ++i) {
            auto [a, b, c, d] = A[i];
            if (b < a + right[i] || !ranges::binary_search(edges, tuple{a + right[i], c + right[i], -1}))
                continue;
            hot[i] = true;
        }
        G = vector<vector<int>>(N, vector<int>(N, inf));
        for (auto i = 0; i < M; ++i) {
            auto [a, b, c, d] = A[i];
            if (hot[i])
                right[i] += 1;
            // assert(right[i] <= b - a + 1);
            for (auto j = 0; j < right[i]; ++j) {
                auto u = a + j;
                auto v = c + j;
                if (d < v) {
                    cout << "No\n";
                    return;
                }
                G[u][v] = min(G[u][v], 0);
                G[v][u] = min(G[v][u], 0);
            }
            if (right[i] == b - a + 1) {
                if (b - a >= d - c) {
                    cout << "No\n";
                    return;
                }
            } else {
                auto u = a + right[i];
                auto v = c + right[i];
                if (d < v) {
                    cout << "No\n";
                    return;
                }
                G[u][v] = -1;
            }
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

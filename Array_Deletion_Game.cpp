#include <bits/stdc++.h>
using namespace std;

int minMoves(const vector<string>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    const int INF = 1e9;

    // Build portals map
    unordered_map<char, vector<pair<int,int>>> portals;
    portals.reserve(26);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            char c = matrix[i][j];
            if (c >= 'A' && c <= 'Z') {
                portals[c].emplace_back(i, j);
            }
        }
    }

    // Distance array
    vector<vector<int>> dist(m, vector<int>(n, INF));
    vector<bool> usedPortal(26, false);

    // Multiset as priority queue: (distance, x, y)
    multiset<tuple<int,int,int>> ms;
    dist[0][0] = 0;
    ms.emplace(0, 0, 0);

    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (!ms.empty()) {
        auto [d, x, y] = *ms.begin();
        ms.erase(ms.begin());
        if (d != dist[x][y]) continue;
        if (x == m-1 && y == n-1) return d;

        // Normal moves (cost = 1)
        for (auto& dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] != '#') {
                int nd = d + 1;
                if (nd < dist[nx][ny]) {
                    // update
                    if (dist[nx][ny] != INF)
                        ms.erase(ms.find(make_tuple(dist[nx][ny], nx, ny)));
                    dist[nx][ny] = nd;
                    ms.emplace(nd, nx, ny);
                }
            }
        }

        // Teleportation (cost = 0)
        char c = matrix[x][y];
        if (c >= 'A' && c <= 'Z' && !usedPortal[c - 'A']) {
            for (auto& p : portals[c]) {
                int px = p.first, py = p.second;
                if (d < dist[px][py]) {
                    if (dist[px][py] != INF)
                        ms.erase(ms.find(make_tuple(dist[px][py], px, py)));
                    dist[px][py] = d;
                    ms.emplace(d, px, py);
                }
            }
            usedPortal[c - 'A'] = true;
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<string> matrix(m);
    for (int i = 0; i < m; ++i) cin >> matrix[i];

    cout << minMoves(matrix) << '\n';
    return 0;
}

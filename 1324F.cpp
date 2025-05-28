#include <bits/stdc++.h>
using namespace std;
 
#define ln '\n'
#define pb push_back
#define ll long long
 
int n;
vector<int> color; // 1 for white, 0 for black
vector<vector<int>> adj;
vector<ll> dp, ans;
 
// First DFS: compute dp[v] = (1 if white, -1 if black) + sum(max(0, dp[child]))
void dfs1(int v, int p) {
    dp[v] = (color[v] == 1 ? 1LL : -1LL);
    for (int u : adj[v]) {
        if(u == p) continue;
        dfs1(u, v);
        dp[v] += max(0LL, dp[u]);
    }
}
 
// Second DFS: re-root DP so that ans[v] becomes the answer for vertex v.
void dfs2(int v, int p) {
    ans[v] = dp[v];
    for (int u : adj[v]) {
        if(u == p) continue;
        ll orig_dp_v = dp[v], orig_dp_u = dp[u];
 
        // Remove u's contribution from v and add parent's contribution to child.
        dp[v] -= max(0LL, dp[u]);
        dp[u] += max(0LL, dp[v]);
 
        dfs2(u, v);
 
        // Restore original values.
        dp[u] = orig_dp_u;
        dp[v] = orig_dp_v;
    }
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    color.resize(n+1);
    for (int i = 1; i <= n; i++){
        cin >> color[i];
    }
    adj.assign(n+1, vector<int>());
    for (int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    dp.assign(n+1, 0);
    ans.assign(n+1, 0);
    
    // Root the tree at vertex 1.
    dfs1(1, 0);
    dfs2(1, 0);
    
    for (int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << ln;
    return 0;
}
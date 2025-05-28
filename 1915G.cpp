#include <bits/stdc++.h>
using namespace std;
 
#define ln                      '\n'
#define F                       first
#define S                       second
#define pb                      push_back
#define ll                      long long
#define int                     long long
#define CNT(x)                  __builtin_popcountll(x)
 
#ifdef RKY_CSE
#include "rky_cse/debug2.h"
#else
#define dbg(... )
#endif
 
const long long N = 2e5+7, mod = 1e9+7, inf = (ll)(1e18)+7;
bool isTc=false; int ctc=1; int ntc=1; 
void rky_cse(); void _tc();
void run(){ _tc(); if(isTc) cin>>ntc; for(ctc=1; ctc<=ntc; ctc++) rky_cse(); }
 
vector<vector<vector<int>>> adj;
vector<int> s;
int n, m;
vector<vector<int>> dist;
int ans = inf;
 
void dj(int src){
    dist[src][ s[src] ] = 0;
    multiset<vector<int>> ms;
    ms.insert({0, s[src], src});
    while(!ms.empty()){
        auto it = ms.begin();
        int d = (*it)[0];
        int mn = (*it)[1];
        int node = (*it)[2];
        ms.erase(it);
        for(auto v : adj[node]){
            int to = v[0];
            int wt = v[1];
            int new_cost = d + wt * mn;
            int new_mn = min(mn, s[to]);
            
            if(new_cost < dist[to][new_mn]){
                dist[to][new_mn] = new_cost;
                ms.insert({new_cost, new_mn, to});
            }
        }
    }
}
 
void prec(){ }
 
int32_t main(){ ios::sync_with_stdio(0); cin.tie(0); prec(); run(); return 0; }
 
void _tc(){ isTc=true; }
 
void rky_cse(){
    cin >> n >> m;
    adj.assign(n+1, vector<vector<int>>());
    for(int i=0; i<m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    s.assign(n+1, 0);
    for(int i=1; i<=n; i++){
        cin >> s[i];
    }
    dist.assign(n+1, vector<int>(1001, inf));
    dj(1);
    int best = inf;
    for(int i=0; i<1001; i++){
        best = min(best, dist[n][i]);
    }
    cout << best << ln;
}
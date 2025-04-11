#include <bits/stdc++.h>
using namespace std;
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//typedef tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key

//MARK:- MACROS================================================================
#define ln                      '\n'
#define F                       first
#define S                       second
#define yes                     cout<<"YES"<<ln;
#define no                      cout<<"NO"<<ln;
#define ll                      long long
#define int                     long long
#define i128                    __int128_t
#define ui128                   __uint128_t
#define CNT(x)                  __builtin_popcountll(x);
#define pb                      push_back
#define vll                     vector<ll>
#define vvll                    vector<vll>
#define all(a)                  a.begin(), a.end()
#define MAX(x)                  *max_element(all(x));
#define MIN(x)                  *min_element(all(x));
#define SUM(x)                  accumulate(all(x), 0LL);
                    
//MARK:- DEBUGGER==============================================================
#ifdef RKY_CSE
#include "rky_cse/debug2.h"
#else
#define dbg(... )
#endif

vector<long long>fact_dp;
ll power( ll x, ll y, ll p){ ll res = 1; x = x % p; while (y > 0) { if (y & 1) res = (res * x) % p; y = y >> 1; x = (x * x) % p; } return res; }
ll modInverse(ll n,ll p){ return power(n, p - 2, p); }
ll factorial( ll num, ll mod){ if( ::fact_dp.size() == 0){ ::fact_dp.push_back( 1); } for( int i = ::fact_dp.size(); i <= num; i++){ ::fact_dp.push_back( ( ::fact_dp[ i - 1] * ( i % mod)) % mod); } return ::fact_dp[ num]; }
ll combinate(ll n, ll r, ll p){ if (n < r)  return 0LL; if (r == 0LL) return 1LL;return (factorial(n,p) * modInverse(factorial(r,p), p) % p *modInverse(factorial(n-r,p), p) % p) % p; }
ll permutate(ll n, ll r, ll p){ if (r == 0) return 1LL; return (factorial(n,p) * modInverse( factorial(n - r, p), p)) % p; }
mt19937_64 gen(chrono::system_clock::now().time_since_epoch().count());
ll rng(ll mn, ll mx){uniform_int_distribution<ll> dis(mn, mx);return dis(gen);}

//MARK:- SNIPPETS =============================================================
//fl-for loop||flj,flk for loop j,k||flr rev for loop lc-lower case,uc-upper case 
//tc-test case || pf-prime function O(sqrt(n) || bns-binary search
//sv-sieve || sqb-square root using binary search || sbc sort by condition
//bnp binpow || bnpm binpow mod || exgcd gcdExtended ||kmp KMP algo for string prefix
// rbnk rabin korp string matching || cmp comparator|| mpd max prime divisor using seive
//sgtS segment tree for sum|| sgtMx segment tree for Max
//nck nCk in O(n^2) dp ||cntd counting divisor logn||pmf prime factors
//oms ordered_multiset || blf binary lifting || dsu unionbysize|| lsv linear seive
//lsv linear seive O(n) + pf in O(logn)
/*------------------------------------------------------------------------------------*/
#include <bits/stdc++.h>
using namespace std;
 
#define ln '\n'
#define pb push_back
#define ll long long
#define int long long
 
const int INF = -1e9;
 
int n;
vector<vector<int>> adj;
vector<int> dwn, up;
 
void dfs1(int u, int p){
    dwn[u]=0;
    for(auto v: adj[u]){
        if(v==p) continue;
        dfs1(v,u);
        dwn[u]=max(dwn[u], dwn[v]+1);
    }
}
 
void dfs2(int u, int p){
    vector<int> ch, vals;
    for(auto v: adj[u]){
        if(v==p) continue;
        ch.pb(v);
        vals.pb(dwn[v]+1);
    }
    int m = vals.size();
    vector<int> pre(m), suf(m);
    for(int i=0;i<m;i++){
        pre[i] = (i==0? vals[i] : max(pre[i-1], vals[i]));
    }
    for(int i=m-1;i>=0;i--){
        suf[i] = (i==m-1? vals[i] : max(suf[i+1], vals[i]));
    }
    for(int i=0;i<m;i++){
        int v = ch[i];
        int cand = INF;
        if(i>0) cand = max(cand, pre[i-1]);
        if(i<m-1) cand = max(cand, suf[i+1]);
        int ext = max(up[u]+1, cand);
        up[v] = ext;
        dfs2(v,u);
    }
}
 
int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    adj.assign(n+1, vector<int>());
    for(int i=1;i<n;i++){
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dwn.assign(n+1,0);
    up.assign(n+1,0);
    dfs1(1,0);
    up[1]=0;
    dfs2(1,0);
    int ans = dwn[1];
    for(int i=2;i<=n;i++){
        ans = max(ans, up[i] + 1 + dwn[i]);
    }
    cout << ans << ln;
    return 0;
}
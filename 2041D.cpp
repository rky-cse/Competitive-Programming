//https://codeforces.com/problemset/problem/2041/D

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

//MARK:- CONSTANTS=============================================================
const long long  N = 2e5+7;
const long long  mod=1e9+7;
const long long  inf = (ll)(1e18)+7;
bool isTc=false;int ctc=1;int ntc=1;void rky_cse();void _tc();
void run(){_tc();if(isTc)cin>>ntc;for(ctc=1;ctc<=ntc;ctc++)rky_cse();}

//MARK:- Supplimentary Functions===============================================

class node{
    public:
    int x,y;
    int dist;
    char last;
    int cnt;    
};

int n,m;
bool ck(int i,int j){
    return i>=0 && i<n && j>=0 && j<m;

}



void prec(){          }

int32_t main(){ ios::sync_with_stdio(0);cin.tie(0);prec();run();}

void _tc(){                         //isTc=true;
}
void rky_cse(){
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++){
        cin >> s[i];
    }
    
    int sx, sy;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (s[i][j] == 'S'){
                sx = i;
                sy = j;
                break;
            }
        }
    }
    
    vector<vector<vector<vector<bool>>>> vis(
        n, vector<vector<vector<bool>>>(m, vector<vector<bool>>(5, vector<bool>(3, false))));
    
    queue<node> q;
    node start;
    start.x = sx; start.y = sy; start.dist = 0;
    start.last = 'N'; start.cnt = 0; // no move yet
    vis[sx][sy][0][0] = true;
    q.push(start);
    
    auto pushState = [&](int nx, int ny, char d, int newCnt, int newDist) {
        // Map direction to index:
        int dIdx;
        if(d=='R') dIdx = 1;
        else if(d=='L') dIdx = 2;
        else if(d=='D') dIdx = 3;
        else if(d=='U') dIdx = 4;
        else dIdx = 0; // 'N'
        
        if(!vis[nx][ny][dIdx][newCnt - 1]){
            vis[nx][ny][dIdx][newCnt - 1] = true;
            node temp;
            temp.x = nx;
            temp.y = ny;
            temp.dist = newDist;
            temp.last = d;
            temp.cnt = newCnt;
            q.push(temp);
        }
    };
    
    while(!q.empty()){
        node cur = q.front();
        q.pop();
        int x = cur.x, y = cur.y;
        if(s[x][y]=='T'){
            cout << cur.dist << "\n";
            return;
        }
    
        
        // RIGHT
        if(ck(x, y+1) && s[x][y+1] != '#'){
            int newCnt = (cur.last=='R' ? cur.cnt+1 : 1);
            if(newCnt <= 3)
                pushState(x, y+1, 'R', newCnt, cur.dist+1);
        }
        // LEFT
        if(ck(x, y-1) && s[x][y-1] != '#'){
            int newCnt = (cur.last=='L' ? cur.cnt+1 : 1);
            if(newCnt <= 3)
                pushState(x, y-1, 'L', newCnt, cur.dist+1);
        }
        // DOWN
        if(ck(x+1, y) && s[x+1][y] != '#'){
            int newCnt = (cur.last=='D' ? cur.cnt+1 : 1);
            if(newCnt <= 3)
                pushState(x+1, y, 'D', newCnt, cur.dist+1);
        }
        // UP
        if(ck(x-1, y) && s[x-1][y] != '#'){
            int newCnt = (cur.last=='U' ? cur.cnt+1 : 1);
            if(newCnt <= 3)
                pushState(x-1, y, 'U', newCnt, cur.dist+1);
        }
    }
    cout << -1 << "\n";
    

}
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




void prec(){          }

int32_t main(){ ios::sync_with_stdio(0);cin.tie(0);prec();run();}

void _tc(){                         isTc=true;
}
void rky_cse(){
    int n;cin>>n;

    vll a(n);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    multiset<int>se,so;

    for(int i=0;i<n;i++){
        if(a[i]%2)so.insert(a[i]);
        else se.insert(a[i]);
    }

    int mx=0;
    int mxp=0;

    if(se.empty()){
        mx = *so.rbegin();
        mxp = 1;
        so.erase(--so.end());
    }
    else if(so.empty()){
        mx = *se.rbegin();
        mxp = 0;
        se.erase(--se.end());
    }
    else if(*se.rbegin() > *so.rbegin()){
        mx = *se.rbegin();
        mxp = 0;
        se.erase(--se.end());
    }
    else{
        mx = *so.rbegin();
        mxp = 1;
        so.erase(--so.end());
    }
    


    while(true){
        if(mxp==0 and so.size()==0){
            cout<<mx<<ln;
            return;
            
        }
        if(mxp==1 and se.size()==0){
            cout<<mx<<ln;
            return;
            
        }
        if(mxp==0){
            int tpo=(*so.rbegin());

            if(tpo>2){
                mx+=tpo-2;
                se.insert(2);
                so.erase(--so.end());
                mxp=mx%2;

            }
            else{
                break;
            }
            



        }
        else{
            int tpe=(*se.rbegin());
            if(tpe>1){
                mx+=tpe-1;
                so.insert(1);
                se.erase(--se.end());
                mxp=mx%2;
            }
            else{
                break;
            }
            
            
        }
        dbg(se)
        dbg(so)
        dbg(mx,mxp)
    }


    while(true){
        if(mxp==0 and so.size()==0){
            cout<<mx<<ln;
            return;
            
        }
        if(mxp==1 and se.size()==0){
            cout<<mx<<ln;
            return;
            
        }
        if(mxp==0){
            int tpo=(*so.rbegin());

            if(tpo>0){
                mx+=tpo;
                so.erase(--so.end());
                mxp=mx%2;

            }
            else{
                break;
            }
            



        }
        else{
            int tpe=(*se.rbegin());
            if(tpe>0){
                mx+=tpe;
                se.erase(--se.end());
                mxp=mx%2;
            }
            else{
                break;
            }
            
            
        }
        dbg(se)
        dbg(so)
        dbg(mx,mxp)
    }

    

    cout<<mx<<ln;   


        




}
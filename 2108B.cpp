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
bool ck(string &a,string &b,string &c,map<char,int>&mp){

    int n=c.size();

    int sa=a.size();
    int sb=b.size();

    int carry=0;
    int j=0;

    for(int i=0;i<n;i++){

        int sum=mp[c[i]];

        int x=0, y=0;

        if(i<a.size()){
            x=mp[a[i]];

        }
        if(i<b.size()){
            y=mp[b[i]];
        }
    

        int d=(x+y+carry)%10;   
        carry=(x+y+carry)/10;
        if(d!=sum){
            return false;
        }

    }

    if(carry!=0){
        return false;
    }  

    return true;

}



void prec(){          }

int32_t main(){ ios::sync_with_stdio(0);cin.tie(0);prec();run();}

void _tc(){                         //isTc=true;
}
void rky_cse(){
    string a,b,c;
    cin>>a>>b>>c;

    reverse(all(a));
    reverse(all(b));
    reverse(all(c));

    set<char>st;

    for(auto i:a)st.insert(i);
    for(auto i:b)st.insert(i);
    for(auto i:c)st.insert(i);

    if(st.size() > 10){
        no
        return;
    }

    vector<int>v(10,0);

    int k=st.size();

    for(int i=0;i<k;i++){
        v[i]=1;
    }  
    
    sort(all(v));

    //dbg("here")

    do{
        vector<int>sl;

        for(int i=0;i<10;i++){
            if(v[i]){
                sl.pb(i);
            }
        }
        
        vector<int>p(k);
        for(int i=0;i<k;i++){
            p[i]=i;
        }

        do{

            //dbg("here",sl,p)
            map<char,int>mp;
            int j=0;
            for(auto &it:st){
                mp[it]=sl[p[j++]];
            }

            if(ck(a,b,c,mp)){

                yes;

                
                return;
            }

            

        }while(next_permutation(all(p)));

    }while(next_permutation(all(v)));

    no;
}
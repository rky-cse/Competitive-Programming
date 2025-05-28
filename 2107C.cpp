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
    int n,k;cin>>n>>k;

    string s;cin>>s;
    s="1"+s+"1";

    vector<int>a(n+2,-inf);

    for(int i=1;i<=n;i++){
        cin>> a[i];
    }

    dbg(s,a)


    string b=s;
    sort(all(b));

    if(b[0]=='1'){
        int cur=0;
        int mx=-inf;
        for(int i=1;i<=n;i++){
            cur=max(a[i],a[i]+cur);
            mx=max(mx,cur);

        }

        dbg(mx,"here")
        if(mx!=k){
            cout<<"No\n";
            return;
        }

        dbg("here")

        cout<<"Yes\n";  

        for(int i=1;i<=n;i++){
            cout<<a[i]<<" ";
        }
        cout<<ln;
        return;
    }

    vector<pair<int,vector<int>>>vp;

    char l='0';

    vector<int>temp;

    for(int i=0;i<n+2;i++){
        if(s[i]==l){
            if(l=='1'){
                temp.pb(a[i]);
                
            }
            else{
                temp.pb(0);
            }


        }
        else{
            if(l=='1'){

                if(temp.size()){
                    vp.pb({1,temp});
                    temp.clear();

                }

                
          
                
                temp.pb(0);
                l='0';
            }
            else{
                if(temp.size()){
                    vp.pb({0,temp});
                    temp.clear();

                }

                temp.pb(a[i]);
                l='1';
            }
        }
    }  
    
    if(temp.size()){
        if(l=='1'){
            vp.pb({1,temp});
        }
        else{
            vp.pb({0,temp});
        }
    } 
    
    dbg(vp)



    int sz=vp.size();

    vector<pair<int,vector<int>>>vv;

    for(int i=0;i<sz;i++){
        if(vp[i].F==1){
            int cur=0;
            int mx=-inf;
            for(auto &it:vp[i].S){
                cur=max(it,it+cur);
                mx=max(mx,cur);

            }

            vector<int>temp;
            temp.pb(mx);


            int szv=vp[i].S.size();
            cur=0;
            mx=-inf;
            for(int j=0;j<szv;j++){
                cur+=vp[i].S[j];
                mx=max(mx,cur);
            }
            temp.pb(mx);
            mx=-inf;
            cur=0;

            for(int j=szv-1;j>=0;j--){
                cur+=vp[i].S[j];
                mx=max(mx,cur);
            }
            temp.pb(mx);

            vv.push_back({1,temp});
        }
        else{
            vv.push_back({0,vp[i].S});
        }
    } 
    
    dbg(vv)    


    sz=vv.size();

    for(int i=0;i<sz;i++){

        if(vp[i].F==1 and vv[i].S[0]>k){
            cout<<"No\n";
            return;
        }
    
          
    }

    int idx=-1;


    for(int i=1;i<sz-1;i++){
        

        if(vv[i].F==0){

            
            int sfxA=max(0LL,vv[i-1].S[2]);
            int pfxB=max(0LL,vv[i+1].S[1]);

            int x=k-sfxA-pfxB;


            int cr=sfxA+x+pfxB;

            int mx=max({vv[i-1].S[0],cr,vv[i+1].S[0]});

            if(mx==k){
                vv[i].S[0]=x;
                idx=i;
                break;
            }

        }
        

        
    }

    int df=-1e18;

    if(idx==-1){

        for(int i=0;i<sz;i++){
            if(vv[i].F==1){
                if(vv[i].S[0]==k){
                    

                    vector<int>ans;

                    for(auto &it:vp){
                        for(auto &itt:it.S){
                            if(it.F==1){
                                ans.pb(itt);
                            }
                            else{
                                ans.pb(df);
                            }
                            

                        }
                    }

                    int cur=0;

                    int mx=-inf;



                    for(int j=0;j<n+2;j++){
                        cur=max(ans[j],ans[j]+cur);
                        mx=max(mx,cur);
                        
                    }
                    if(mx!=k or ans.size()!=n+2){
                        while(true);
                    }

                    cout<<"Yes\n";
                    for(int j=1;j<=n;j++){
                        cout<<ans[j]<<" ";
                    }


                    cout<<'\n';
                    return;
                }
                
            }
        }


        while(true);


        cout<<"No\n";
        
        return;
    }

    for(int i=0;i<sz;i++){
        if(vv[i].F==0 and i!=idx){
            vv[i].S[0]=df;
        }
    }




    for(int i=0;i<sz;i++){
        if(vv[i].F==0){
            int szv=vv[i].S.size();

            for(int j=0;j<szv;j++){
                vp[i].S[j]=vv[i].S[j];
            }
        }
    }

    vector<int>ans;

    for(int i=0;i<sz;i++){
        
        int szv=vp[i].S.size();

        for(int j=0;j<szv;j++){
            ans.pb(vp[i].S[j]);
        }
        
    }

    dbg(ans)

    int cur=0;

    int mx=-inf;



    for(int i=1;i<=n;i++){
        cur=max(ans[i],ans[i]+cur);
        mx=max(mx,cur);
        
    }
    if(mx!=k or ans.size()!=n+2){
        while(true);
    }

    cout<<"Yes\n";

    

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<ln;   




    
}
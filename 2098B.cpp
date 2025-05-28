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
//https://cses.fi/paste/1c6ce2b91fae3887a7617e/
template <typename ArrayType, typename SegmentType>
class LazySegmentTree {
private:
    vector<SegmentType> sgt, lazy;
    int n_elements;
/****you should update this block according to requirements***************************/

    SegmentType identity_element=0;// change this if required
    SegmentType identity_update=0;// change this if required

    SegmentType merge(SegmentType a, SegmentType b) {
        return a + b; // Modify this for other operations (e.g., min, max)
        return min(a,b);
        return max(a,b);
    }
    void lazy_propagate(int v, int tl, int tr) {
        /*for sum */

        if (lazy[v] != identity_update) {
            sgt[v] += lazy[v] * (tr - tl + 1);
            if (tl != tr) { // Not a leaf node
                lazy[2 * v] += lazy[v];
                lazy[2 * v + 1] += lazy[v];
            }
            lazy[v] = identity_update;
        }

        /*for other op like min max*/

        // if (lazy[v] != identity_update) {
        //     sgt[v] =merge(lazy[v],sgt[v]);
        //     if (tl != tr) { // Not a leaf node
        //         lazy[2 * v] = merge(lazy[2*v],lazy[v]);
        //         lazy[2 * v + 1] = merge(lazy[2*v+1],lazy[v]);
        //     }
        //     lazy[v] = identity_update;
        // }
    }

    /********************************************************************************/

    void build(int v, int tl, int tr, const vector<ArrayType>& arr) {
        if (tl == tr) {
            sgt[v] = static_cast<SegmentType>(arr[tl]);  // Convert ArrayType to SegmentType
        } else {
            int tm = (tl + tr) / 2;
            build(2 * v, tl, tm, arr);
            build(2 * v + 1, tm + 1, tr, arr);
            sgt[v] = merge(sgt[2 * v], sgt[2 * v + 1]);
        }
    }

    

    SegmentType query(int v, int tl, int tr, int l, int r) {
        lazy_propagate(v, tl, tr);

        // If the query range [l, r] is outside the node range [tl, tr]
        if (tl > r || tr < l) return identity_element;
        
        // If the query range completely covers the node range
        if (l <= tl && tr <= r) return sgt[v];

        int tm = (tl + tr) / 2;
        return merge(query(2 * v, tl, tm, l, r),
                     query(2 * v + 1, tm + 1, tr, l, r));
    }

    void update_range(int v, int tl, int tr, int l, int r, SegmentType val) {
        lazy_propagate(v, tl, tr);

        // If the update range [l, r] is outside the node range [tl, tr]
        if (tl > r || tr < l) return;

        // If the update range completely covers the node range
        if (l <= tl && tr <= r) {
            lazy[v] = merge(lazy[v], val);
            lazy_propagate(v, tl, tr);
            return;
        }

        int tm = (tl + tr) / 2;
        update_range(2 * v, tl, tm, l, r, val);
        update_range(2 * v + 1, tm + 1, tr, l, r, val);
        sgt[v] = merge(sgt[2 * v], sgt[2 * v + 1]);
    }
    void update_point(int v, int tl, int tr, int pos, SegmentType new_value) {
        lazy_propagate(v, tl, tr);
        if (tl == tr) {
            sgt[v] = new_value;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update_point(2 * v, tl, tm, pos, new_value);
            } else {
                update_point(2 * v + 1, tm + 1, tr, pos, new_value);
            }
            sgt[v] = merge(sgt[2 * v], sgt[2 * v + 1]);
        }
    }

public:
    // Constructor with array to build the segment tree
    LazySegmentTree(const vector<ArrayType>& arr) 
        : n_elements(arr.size()) {
        sgt.resize(4 * n_elements, identity_element);
        lazy.resize(4 * n_elements, identity_update);
        build(1, 0, n_elements - 1, arr);
    }

    SegmentType query(int l, int r) {
        return query(1, 0, n_elements - 1, l, r);
    }

    void update_range(int l, int r, SegmentType addend) {
        update_range(1, 0, n_elements - 1, l, r, addend);
    }
    void update_point(int pos, SegmentType val) {
        update_point(1,0,n_elements-1,pos,val);
    }


};



void prec(){          }

int32_t main(){ ios::sync_with_stdio(0);cin.tie(0);prec();run();}

void _tc(){                         isTc=true;
}
void rky_cse(){
    int n,k;cin>>n>>k;

    vll a(n);


    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    sort(all(a));
    dbg(a)

    int lf = (n-k+1)/2 - 1 ;
    int rt = n-1-lf;
    dbg(lf,rt)

    cout<<a[rt]-a[lf]+1<<ln;  


  
}
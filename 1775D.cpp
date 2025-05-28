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

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int s, t;
    cin >> s >> t;
    s--; t--;
    if (s == t) {
        cout << 1 << '\n' << s + 1 << '\n';
        return 0;
    }
   
    if (a[s] == 1 || a[t] == 1) {
        cout << -1 << '\n';
        return 0;
    }
    int maxA = *max_element(a.begin(), a.end());
    vector<int> spf(maxA + 1);
    for (int i = 2; i <= maxA; i++) {
        if (spf[i] == 0) {
            for (int j = i; j <= maxA; j += i) if (spf[j] == 0)
                spf[j] = i;
        }
    }
    
    vector<vector<int>> spiderPrimes(n);
    vector<vector<int>> primeSpiders(maxA + 1);
    for (int i = 0; i < n; i++) {
        int x = a[i];
        while (x > 1) {
            int p = spf[x];
            spiderPrimes[i].push_back(p);
            x /= p;
            while (x % p == 0) x /= p;
        }
        for (int p : spiderPrimes[i])
            primeSpiders[p].push_back(i);
    }
    vector<char> visSpider(n), visPrime(maxA + 1);
    vector<int> parSpider(n, -1), parPrime(maxA + 1, -1);
    queue<pair<int,int>> q;
    visSpider[s] = 1;
    q.push({s, 0}); // type 0 = spider, 1 = prime
    bool found = false;
    while (!q.empty() && !visSpider[t]) {
        auto [u, type] = q.front();
        q.pop();
        if (type == 0) {
            // spider -> primes
            for (int p : spiderPrimes[u]) {
                if (!visPrime[p]) {
                    visPrime[p] = 1;
                    parPrime[p] = u;
                    q.push({p, 1});
                }
            }
        } else {
            // prime -> spiders
            for (int v : primeSpiders[u]) {
                if (!visSpider[v]) {
                    visSpider[v] = 1;
                    parSpider[v] = u;
                    q.push({v, 0});
                    if (v == t) { found = true; break; }
                }
            }
        }
        if (found) break;
    }
    if (!visSpider[t]) {
        cout << -1 << '\n';
        return 0;
    }
 
    vector<int> path;
    int cur = t;
    while (cur != s) {
        path.push_back(cur + 1);
        int p = parSpider[cur];
        cur = parPrime[p];
    }
    path.push_back(s + 1);
    reverse(path.begin(), path.end());
    cout << path.size() << '\n';
    for (int x : path) cout << x << ' ';
    cout << '\n';
    return 0;
}

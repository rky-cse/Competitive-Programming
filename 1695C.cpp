#include <bits/stdc++.h>
using namespace std;
 
#define ln '\n'
#define pb push_back
#define ll long long
#define int long long
 
const long long MAXX = 1 << 19;
const long long inf = (ll)(1e18)+7;
 
bool isTc=false; int ctc=1, ntc=1; 
void rky_cse(); void _tc();
void run(){ _tc(); if(isTc) cin>>ntc; for(ctc=1; ctc<=ntc; ctc++) rky_cse(); }
 
int n, m;
vector<vector<int>> dp, a;
 
int fun(int i, int j, int t) {
    if(i == n-1 && j == m-1) return a[i][j];
    if(i == n-1) return a[i][j] + fun(i, j+1, t);
    if(j == m-1) return a[i][j] + fun(i+1, j, t);
    if(dp[i][j] != -1) return dp[i][j];
    int ans;
    if(t == 0) ans = -inf;
    else ans = inf;
    if(t == 0)
        ans = max(a[i][j] + fun(i+1, j, t), a[i][j] + fun(i, j+1, t));
    else
        ans = min(a[i][j] + fun(i+1, j, t), a[i][j] + fun(i, j+1, t));
    return dp[i][j] = ans;
}
 
void prec(){ }
 
int32_t main(){ ios::sync_with_stdio(0); cin.tie(0); prec(); run(); }
void _tc(){ isTc=true; }
 
void rky_cse(){
    cin >> n >> m;
    dp.assign(n, vector<int>(m, -1));
    a.assign(n, vector<int>(m, 0));
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> a[i][j];
        }
    }
    int mn = fun(0,0,1);
    dp.assign(n, vector<int>(m, -1));
    int mx = fun(0,0,0);
    if((n+m) % 2 == 0){
        cout << "NO" << ln;
        return;
    }
    if(mn <= 0 && mx >= 0) cout << "YES" << ln;
    else cout << "NO" << ln;
}
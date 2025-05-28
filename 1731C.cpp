#include <bits/stdc++.h>
using namespace std;
 
#define ln '\n'
#define pb push_back
#define ll long long
#define int long long
 
const long long MAXX = 1 << 19;  // ~524288
 
bool isTc=false; int ctc=1, ntc=1; 
void rky_cse(); void _tc();
void run(){ _tc(); if(isTc) cin >> ntc; for(ctc=1; ctc<=ntc; ctc++) rky_cse(); }
 

 
void prec(){
    
}
 
int32_t main(){ ios::sync_with_stdio(0); cin.tie(0); prec(); run(); }
void _tc(){ isTc=true; }
 
void rky_cse(){
    int n; cin >> n;
    vector<ll> a(n);
    int mx=0;
    for(int i=0;i<n;i++){
        cin >> a[i];
        mx=max(a[i],mx);
    }
    vector<int> oxr;
    for(int i=0;i*i<=2*mx;i++){
        oxr.push_back(i*i);
    }
    vector<int>mp(4*mx,0);
    mp[0] = 1;
    int xr = 0;
    int ans = (n*(n+1))/2;  
    for(int i=0;i<n;i++){
        xr ^= a[i];
        for(auto &s : oxr){
            if(mp[xr ^ s]){
                ans -= mp[xr ^ s];
            }
        }
        mp[xr]++;
    }
    cout << ans << ln;
}
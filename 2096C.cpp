#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<ll> xs(n), ys(n);
        for(int i = 0; i < n; i++){
            cin >> xs[i] >> ys[i];
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        ll s = xs[n/2];
        ll t = ys[n/2];
        cout << s << " " << t << "\n";
    }
    return 0;
}

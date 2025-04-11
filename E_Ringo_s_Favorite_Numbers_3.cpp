#include <bits/stdc++.h>
using namespace std;

const long long nmax = 1000007;
const long long mod = 1000000007;
const long long inf = (long long)(1e18) + 7;
bool tc = false; 
int tc_num = 1; 
int num_tc = 1; 
void solve(); 
void set_tc();

vector<bool> pr(nmax+1, true);
vector<int> cp;
vector<long long> nums;

void sieve() {
    for (int i = 2; i * i <= nmax; i++) {
        if (pr[i]) {
            for (int j = i * i; j <= nmax; j += i)
                pr[j] = false;
        }
    }
}

void prec() { 
    pr[0] = pr[1] = false;
    sieve();
    for (int i = 2; i <= nmax; i++) {
        if (pr[i])
            cp.push_back(i);
    }
    const long long LIM = 1000000; // sqrt(1e12)
    for (int i = 0; i < (int)cp.size() && cp[i] <= LIM; i++) {
        long long cur1 = cp[i];
        while (true) {
            if (cur1 > LIM) break;
            for (int j = i+1; j < (int)cp.size() && cp[j] <= LIM; j++) {
                long long cur2 = cp[j];
                while (true) {
                    if (cur2 > LIM) break;
                    if (cur1 > LIM / cur2) break;
                    long long m = cur1 * cur2;
                    if (m > LIM) break;
                    long long cand = m * m;
                    if (cand <= 1000000000000LL)
                        nums.push_back(cand);
                    else break;
                    if (cur2 > LIM / cp[j]) break;
                    cur2 *= cp[j];
                }
            }
            if (cur1 > LIM / cp[i]) break;
            cur1 *= cp[i];
        }
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
}

void run() {
    set_tc();
    if(tc) 
        cin >> num_tc;
    for(tc_num = 1; tc_num <= num_tc; tc_num++)
        solve();
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    prec();
    run();
}

void set_tc() {                         
    tc = true;
}

void solve() {
    long long a; 
    cin >> a;
    int idx = upper_bound(nums.begin(), nums.end(), a) - nums.begin();
    idx--;
    cout << nums[idx] << "\n";
}

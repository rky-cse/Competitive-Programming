#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter the sum n: ";
    cin >> n;
    
    // If n is odd, no combinations are possible using coins 2 and 4.
    if(n % 2 != 0) {
        cout << "Number of ways: 0" << endl;
        return 0;
    }
    
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;  // Base case: one way to form sum 0 (using no coins)
    
    int coins[2] = {2, 4};
    
    // Process each coin. This ensures that the order of coins is not counted as different.
    for (int j = 0; j < 2; j++) {
        for (int i = coins[j]; i <= n; i++) {
            dp[i] += dp[i - coins[j]];
        }
    }
    
    cout << "Number of ways: " << dp[n] << endl;
    return 0;
}

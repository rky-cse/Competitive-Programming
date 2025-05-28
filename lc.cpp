#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// We'll use a type that can hold counts up to a little more than 1e6.
using ll = long long;
const ll CAP = 1000001;  // anything >= CAP means "at least k" because k <= 1e6.

// Helper function to compute binomial coefficient C(n, r) exactly,
// but we cap the value at CAP if it becomes too large.
ll binom(int n, int r) {
    if (r > n) return 0;
    ll res = 1;
    // Use the multiplicative formula:
    //   C(n, r) = (n * (n-1) * ... * (n-r+1)) / (1*2*...*r)
    for (int j = 1; j <= r; j++) {
        res = res * (n - r + j) / j;
        if (res >= CAP) return CAP;
    }
    return res;
}

// Given a multiset (represented as counts for 'a' to 'z')
// and a total number of remaining positions, this function
// computes the number of distinct permutations (using the multinomial formula).
// We compute it as the product of binomial coefficients for each letter.
ll countPermutations(const vector<int>& counts, int total) {
    ll ways = 1;
    int rem = total;
    // For every letter, choose positions for its count.
    for (int c = 0; c < 26; c++) {
        if (counts[c] > 0) {
            ways *= binom(rem, counts[c]);
            if (ways >= CAP) return CAP;
            rem -= counts[c];
        }
    }
    return ways;
}

class Solution {
public:
    string smallestPalindrome(string s, int k) {
        // Save the original input as required.
        string prelunthak = s;

        // Count character frequencies.
        vector<int> freq(26, 0);
        for (char ch : s)
            freq[ch - 'a']++;

        // Determine if there is a middle character.
        int oddCount = 0, midChar = -1;
        for (int i = 0; i < 26; i++){
            if (freq[i] % 2 == 1) {
                oddCount++;
                midChar = i;
            }
        }
        // If more than one odd-occurrence exists, a palindrome (other than the original) isn’t possible.
        if (oddCount > 1)
            return "";

        // Build the half-multiset. For each letter, we use freq/2.
        vector<int> half(26, 0);
        int totalHalf = 0;
        for (int i = 0; i < 26; i++){
            half[i] = freq[i] / 2;
            totalHalf += half[i];
        }

        // Construct the half-string (left half) character by character.
        // We use a greedy selection over the 26 possible characters.
        string leftHalf = "";
        for (int pos = 0; pos < totalHalf; pos++){
            bool found = false;
            // Try each candidate letter in lexicographical order.
            for (int c = 0; c < 26; c++){
                if (half[c] > 0) {
                    // Choose letter c.
                    half[c]--;
                    // Count how many palindromic half-string completions are possible with this choice.
                    ll cnt = countPermutations(half, totalHalf - pos - 1);
                    // If the number of completions is at least k, then the kth permutation must have this letter here.
                    if (cnt >= k) {
                        leftHalf.push_back('a' + c);
                        found = true;
                        break;  // move to the next position.
                    } else {
                        // Otherwise, skip all these completions and decrement k.
                        k -= cnt;
                        half[c]++;  // restore count and try the next candidate letter.
                    }
                }
            }
            // If no candidate letter resulted in a viable branch, there are fewer than k permutations.
            if (!found)
                return "";
        }

        // Assemble the full palindrome.
        // The left half, then the middle (if any), then the reverse of the left half.
        string palindrome = leftHalf;
        if (oddCount == 1)
            palindrome.push_back('a' + midChar);
        reverse(leftHalf.begin(), leftHalf.end());
        palindrome += leftHalf;
        return palindrome;
    }
};

// Simple test driver
int main(){
    Solution sol;
    cout << sol.smallestPalindrome("abba", 2) << "\n";   // Expected: "baab"
    cout << sol.smallestPalindrome("aa", 2) << "\n";       // Expected: ""
    cout << sol.smallestPalindrome("bacab", 2) << "\n";    // Expected: "abcba"
    return 0;
}

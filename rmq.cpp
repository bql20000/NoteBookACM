#include <iostream>
#include <math.h>
#include <algorithm>
#include <unordered_map>

// Problem: 475D Codeforce
// Status: TLE (3e5 * log2(N) * log2(N))

// Sample querying GCD(l..r) using RMQ

using namespace std;
const int N = 1e5 + 8;
const int logN = 17;

int n, a[N], rmq[N][logN+1];

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

void initRMQ() {
    for (int i = 1; i <= n; ++i) rmq[i][0] = a[i];
    for (int k = 1; k <= logN; ++k)
        for (int i = 1; i <= n; ++i) {
            int j = i + (1<<(k-1));
            if (j <= n) rmq[i][k] = gcd(rmq[i][k-1], rmq[j][k-1]);
            else 
                rmq[i][k] = rmq[i][k-1]; 
        }
}

int getGCD(int l, int r) {
    int cur = 0;
    for (int i = 0; i <= logN; ++i)  // loop from 0 is oke here since the range is known (r-l+1)
        if ( (1<<i) & (r-l+1) ) {
            cur = gcd(cur, rmq[l][i]);
            l += (1<<i);
        }
    return cur;

}


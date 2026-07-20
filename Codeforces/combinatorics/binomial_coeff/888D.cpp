#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

using namespace std;


int fact[1001];
int dp[1001][1001];
int main()
{
   
    int n, k;
    cin >> n >> k;


    dp[0][0] = 1;
    dp[1][0] = 1;
    dp[1][1] = 0;


    fact[1] = 1;
    for(int i = 2; i <= 1000; i++)
        fact[i] = fact[i-1] * i;    


    for(int i = 2; i <= n; i++)
    {
        dp[i][0] = fact[i];
        for(int j = 1; j <= i-1; j++)
            dp[i][j] = j*dp[i-1][j-1] + (i-j)*dp[i-1][j];
        dp[i][i] = (i-1) * dp[i-1][i-2];
    }


    unsigned long long sum = 0;

    unsigned long long prod = 1;

    for(int i = n-k; i <= n; i++)
    {
        prod = 1;

        for(int j = n; j > i; j--)
        {
            prod *= j;
        }

        for(int j = n-i; j >= 1; j--)
        {
            prod/=j;
        }

        sum += prod * dp[n-i][n-i];
    }
    cout << sum << endl;
        
    return 0;
}

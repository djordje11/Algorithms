#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
 
using namespace std;
 
short c[501];
bool dp[501][501][501];

int main()
{
    int n, k;
    cin >> n >> k;
 
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i]; 
    }
 
    dp[0][0][0] = true; 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            for (int z = 0; z <= j; z++)
            {
                dp[j][i][z] |= dp[j][i - 1][z];
                if (j - c[i] >= 0)
                {
                    dp[j][i][z] |= dp[j - c[i]][i - 1][z];
                    if(z - c[i] >= 0)
                        dp[j][i][z] |= dp[j - c[i]][i - 1][z-c[i]];
                }
            }   
        }
    }
 
    int cnt = 0;
    for (int i = 0; i <= k; i++)
        if (dp[k][n][i])
            cnt++;
    cout << cnt << endl;
 
    for (int i = 0; i <= k; i++)
        if (dp[k][n][i])
            cout << i << " ";
    cout << endl;
 
    return 0;
} 

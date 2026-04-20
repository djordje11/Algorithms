#include <iostream>
#include <vector>
#include <list>

using namespace std;
int a[2*100000 + 1];
unsigned long long moduo = 998244353;
int dp[2 * 100000 + 2][3];
int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        unsigned long long sum = 0;
        
        dp[0][1] = dp[0][2] = 0;
        int count_ones = 0;
        for (int i = 1; i <= n; i++)
        {
            if (a[i] == 1)
            {
                count_ones++;
                dp[i][2] = dp[i - 1][2];
            }
            else if (a[i] == 2)
            {
                dp[i][2] = count_ones;
               
                if (dp[i - 1][2] != -1)
                {
                    dp[i][2] = (dp[i][2] + (2* dp[i - 1][2])%moduo) % moduo;
                }
            }
            else
            {
                if(dp[i-1][2] != -1)
                    sum = (sum + dp[i - 1][2]) % moduo;
                dp[i][2] = dp[i - 1][2];
            }
        }

        std::cout << sum << std::endl;
    }
    return 0;
}

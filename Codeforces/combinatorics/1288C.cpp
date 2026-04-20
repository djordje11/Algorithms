#include <iostream>
#include <chrono>

int dp[11][1002][1002];
unsigned long long moduo = 1000000000+7;
int main()
{
    int n, m;
    std::cin >> n >> m;

    for(int i = n; i >= 1; i--)
    {
        for(int j = 1; j <= i; j++)
            dp[1][j][i] = 1 + dp[1][j][i+1];
    }

    for(int k = 2; k <= m; k++)
    {
        for(int j = n; j >= 1; j--)
        {
            for(int i = 1; i <= j; i++)
            {
                if(i > 1)
                    dp[k][i][j] = (dp[k][i-1][j] + (moduo - dp[k][i-1][j+1])) % moduo;
                dp[k][i][j] = (dp[k][i][j] + dp[k-1][i][j]) % moduo;
                dp[k][i][j] = (dp[k][i][j] + dp[k][i][j+1]) % moduo;
            }
        }
    }

unsigned long long count = 0 ;
        for(int i = 1; i <= n; i++)
        {
                count = (count + dp[m][i][i]) % moduo;
        }
    std::cout << count << std::endl;

    return 0;
}

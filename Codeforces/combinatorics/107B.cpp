#include <iostream>
#include <set>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <functional>


int main()
{
    int m;
    int n, h;
    int s[1000];
    double dp[100];
    std::cin >> n >> m >> h;


    int sum = 0;
    for (int i = 0; i < m; i++)
    {
        std::cin >> s[i];
        sum += s[i];
    }


    if (sum < n)
    {
        std::cout << -1 << std::endl;
        return 0;
    }
    dp[1] = 0;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + (1 - dp[i - 1]) * (s[h - 1] - 1) / (sum - i + 1);
    }

    std::cout << dp[n] << std::endl;


    return 0;
}

#include <iostream>
using ull = unsigned long long;

ull moduo = 998244353;

ull mul(ull x, ull y)
{
    return x * y >= moduo ? (x*y)% moduo : x*y; 
}
ull add(ull x, ull y)
{
    return x + y >= moduo ? (x+y)% moduo : x+y; 
}

ull bin_exp_map[251][251];

ull bin_exp(ull a, ull b) {

    if(a <= 250 && b <= 250 && bin_exp_map[a][b] != 0)return bin_exp_map[a][b];
    if (b == 0) {
        return 1ULL;
    }
    if (b % 2) {
        return bin_exp(a, b - 1) * 1ULL * a % moduo;
    }
    ull res = bin_exp(a, b / 2);

    if(a <= 250 && b <= 250)
        bin_exp_map[a][b] = res * 1ULL * res % moduo;
    return  res * 1ULL * res % moduo;
}

ull inv(ull a) {
    return bin_exp(a, moduo - 2);
}

ull bin_coef[251][251];
ull dp[251][251];

int main()
{
    int n, k;
    std::cin >> n >> k;


    for(int j = 1; j <= n-1; j++)
    {
        bin_coef[j][0] = 1;
        for(int i = 1; i <= j; i++)
            bin_coef[j][i] = mul(mul(bin_coef[j][i-1], j - i +1 ), inv(i));
    }

    ull tmp = k;
    
    dp[2][1] = 1;
    for(int i = 3; i <= n; i++)
    {
        dp[i][1] = mul(dp[i-1][1], tmp);
        tmp = mul(tmp, k);
    }
    ull sum = dp[n][1];
    for(int i = 2; i <= k; i++)
    {
        dp[2][i] = add(dp[2][i-1], 1);
        for(int j = 3; j <= n; j++)
        {
            ull prod = bin_exp(k-i+1, j-2);
            ull prod_tmp = prod;
            for(int z = 1; z <= j-2; z++)
            {
                dp[j][i] = add(dp[j][i], mul(mul(bin_coef[j-1][z], dp[j-z][i-1]), prod_tmp));
                
                prod = mul(prod, inv(k-i+1));
                prod_tmp = mul(prod_tmp, prod);
            }
            dp[j][i] = add(dp[j][i], prod_tmp);
            dp[j][i] = add(dp[j][i], dp[j][i-1]);
        }
    }
    std::cout << dp[n][k] << std::endl;
    return 0;
}

#include <iostream>
#include <cmath>
#include <vector>
int gcd(int a, int b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}
std::vector<int> extended_gcd(int a, int b)
{
    if(b == 0)
        return {a, 1, 0};
    auto vec = extended_gcd(b, a % b);
    return {vec[0], vec[2], vec[1] - vec[2] * (a / b)};
}

int mod_inv(int a, int m)
{
   // d, m1, n1 = extended_gcd(a,m);
    auto vec = extended_gcd(a,m);
    if(vec[0] != 1)
    {return {};}
    return vec[1] % m > 0 ? vec[1] % m : m + vec[1] % m;
}



long long unsigned inverse[100000] = {1, 1};
int curr = 1;

void initialise(int k )
{
    if(k > curr)
    {
        for(int i = curr + 1; i <= k; i++)
        {
            inverse[i] = (inverse[i-1] * (long long unsigned)mod_inv(i, 1000000007)) % 1000000007;
        }
        curr = k;
    }
}



long long unsigned calc(long long unsigned m, long long unsigned k)
{
    if(k == 0 || k == m) return 1;
    long long unsigned x = m;
    int j = 2;
    initialise(k);
    for(int i = 1; i <k; i++)
            x = (x * (m - i)) % 1000000007;
    return (x * inverse[k]) % 1000000007; 
}

int main()
{
    initialise(1000);
    int k;
    int colors[1000];
    unsigned long long dp[1000];

    std::cin >> k;
    for(int i = 0; i < k; i++)
        std::cin >> colors[i];

    dp[0] = 1;
    unsigned long long sum = colors[0];
    for(int i = 1; i < k; i++)
    {
        dp[i] = ((dp[i-1] % 1000000007) * calc(sum + 1 + colors[i]-1-1, sum) ) % 1000000007;
        sum += colors[i];
    }

    std::cout << dp[k-1] << std::endl;

    return 0;
}

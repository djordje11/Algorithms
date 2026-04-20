#include <iostream>
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
int modInverse(int A, int M)
{
    int m0 = M;
    int y = 0, x = 1;
 
    if (M == 1)
        return 0;
 
    while (A > 1) {
        // q is quotient
        int q = A / M;
        int t = M;
 
        // m is remainder now, process same as
        // Euclid's algo
        M = A % M, A = t;
        t = y;
 
        // Update y and x
        y = x - q * y;
        x = t;
    }
 
    // Make x positive
    if (x < 0)
        x += m0;
 
    return x;
}


long factorial(const int n)
{
    long f = 1;
    for (int i=1; i<=n; ++i)
        f *= i;
    return f;
}
int BinomialCoefficient(const int n, const int k) {
  std::vector<int> aSolutions(k);
  aSolutions[0] = n - k + 1;

  for (int i = 1; i < k; ++i) {
    aSolutions[i] = aSolutions[i - 1] * (n - k + 1 + i) / (i + 1);
  }

  return aSolutions[k - 1];
}

int main()
{
    int n;
    std::cin >> n;
    long long unsigned fact[1000001] = {1};
    
    for(int i = 1; i <= n; i++)
        fact[i] = (i * fact[i-1]) % 998244353;

    
    long long unsigned sum = 1;
    for(int i = 2; i <= n; i++)
    {
        long long unsigned bin_coef = (fact[n] * modInverse(fact[i] * fact[n-i] % 998244353, 998244353)) % 998244353;
        //std::cout << bin_coef << std::endl;
        sum = (sum + (((((bin_coef * (i-1)) % 998244353) * fact[n-i]) % 998244353) * (n - i + 1)) % 998244353) % 998244353;
        //sum += BinomialCoefficient(n, i) * (i-1) * factorial(n - i) * (n-i+1);
    }
    std::cout << sum << std::endl;

}

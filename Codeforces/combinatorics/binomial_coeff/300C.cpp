#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

int ns[100000];
int ks[100000];

using ull = unsigned long long;
unsigned long long moduo = 1000000007;

unsigned long long mul(unsigned long long x, unsigned long long y)
{
    return x * y >= moduo ? (x * y) % moduo : x * y;
}
unsigned long long add(unsigned long long x, unsigned long long y)
{
    return x + y >= moduo ? (x + y) % moduo : x + y;
}

unsigned long long bin_exp(unsigned long long a, unsigned long long b) {
    if (b == 0) {
        return 1ULL;
    }
    if (b % 2) {
        return bin_exp(a, b - 1) * 1ULL * a % moduo;
    }
    unsigned long long res = bin_exp(a, b / 2);
    return res * 1ULL * res % moduo;
}

unsigned long long inv(unsigned long long a) {
    return bin_exp(a, moduo - 2);
}

bool check(ull x, ull a, ull b)
{
    while (x != 0)
    {
        if (x % 10 != a && x % 10 != b)
            return false;
        x = x / 10;
    }
    return true;
}

int main()
{
    
    ull a, b, n;

    cin >> a >> b >> n;

    if (a > b)swap(a, b);

    ull sum = 0;
    ull curr = n * a;

    sum += check(curr, a, b);

    ull prod = 1;
    for (int i = 1; i <= n; i++)
    {
        curr += b - a;
        prod = mul(prod, inv(i));
        prod = mul(prod, n - i + 1);
        if (check(curr, a, b))
        {
            sum = add(sum, prod);
        }

    }
    cout << sum << endl;

    return 0;
}

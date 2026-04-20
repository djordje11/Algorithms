#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

using ull = unsigned long long;
using namespace std;

ull moduo = 1000000007;

ull mul(ull x, ull y)
{
    return x * y >= moduo ? (x*y)% moduo : x*y; 
}
ull add(ull x, ull y)
{
    return x + y >= moduo ? (x+y)% moduo : x+y; 
}

ull bin_exp(ull a, ull b) {
    if (b == 0) {
        return 1ULL;
    }
    if (b % 2) {
        return bin_exp(a, b - 1) * 1ULL * a % moduo;
    }
    ull res = bin_exp(a, b / 2);
    return res * 1ULL * res % moduo;
}

ull inv(ull a) {
    return bin_exp(a, moduo - 2);
}

int a[2 * 100000 + 1];
int fact[4*100000 + 11];

ull bin(ull n, ull k)
{
    if(k == 0 || k == n || n == 1)return 1;
    return mul(fact[n], inv(mul(fact[k], fact[n-k])));
}

int main()
{
    int n;
    cin >> n;


    bool all_zeros = true;
    for(int i = 0; i <= n; i++)
    {
        cin >> a[i];
        if(a[i] > 0)all_zeros = false;
    }

    ull sum = 0;

    if(all_zeros){
        cout << 0 << endl;
        return 0;
    }


    fact[1] = 1;
    for(int i = 2; i <= 4 * 100000 + 10; i++)
        fact[i] = mul(fact[i-1], i);
    

    sum = a[0];

    for(int i = 1; i <= n; i++)
    {
        sum = add(sum , bin(a[i]+i, i+1));
        
    }
    cout << sum << endl;
    
    return 0;
}

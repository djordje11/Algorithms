#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

using ull = unsigned long long;
using namespace std;

ull moduo = 998244353;

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


int ten_pow[2 * 100001];
int main()
{
    int n;
    cin >> n;

    ten_pow[0] = 1;
    for(int i = 1; i <= n; i++)
        ten_pow[i] = mul(10, ten_pow[i-1]);

    for(int i = 1; i <= n-2; i++)
    {
        cout << add(mul(mul(mul(mul(9, 10), 9), ten_pow[n-i-2]), n-i-1),
                mul(10, mul(9, mul(ten_pow[n-i-1], 2))))
        << " ";
    }

    if(n >= 2)
        cout << 180 << " ";
    
    cout << 10 << endl;

    return 0;
}

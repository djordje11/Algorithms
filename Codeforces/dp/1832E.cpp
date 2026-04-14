#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

unsigned long long b[10000001][6];
unsigned long long a[10000001];

unsigned long long moduo = 998244353;

unsigned long long mul(unsigned long long x, unsigned long long y, unsigned long long m)
{
    return x * y >= m ? (x * y) % m : x * y;
}
unsigned long long add(unsigned long long x, unsigned long long y, unsigned long long m)
{
    return x + y >= m ? (x + y) % m : x + y;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long n, x, y, m, k;

    cin >> n >> a[1] >> x >> y >> m >> k;

    
    for (unsigned long long i = 2; i <= n; i++)
        a[i] = add(mul(a[i - 1], x, m), y, m);
    
    unsigned long long sum1 = 0, sum2 = 0;


    for (unsigned long long i = 1; i <= n; i++)
    {
        sum1 = add(sum1, a[i], moduo);
        sum2 = add(sum2, mul(i, a[i], moduo), moduo);
        b[i][1] = moduo - sum2;

        b[i][1] = add(b[i][1], sum1, moduo);
        b[i][1] = add(b[i][1], mul(i, sum1, moduo), moduo);
    }

    for (unsigned long long z = 2; z <= k; z++)
    {
        b[1][z] = 0;
        for (unsigned long long i = 2; i <= n; i++)
            b[i][z] = add(b[i - 1][z],b[i - 1][z - 1], moduo);
    }

    unsigned long long res = 0;


    for (unsigned long long i = 1; i <= n; i++)
    {
        res = res ^ (i * b[i][k]);
    }

    cout << res << endl;
    return 0;
}

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <cstring>
#include <numeric>
#include <chrono>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        unsigned long long n, m;
        cin >> n >> m;
        
        unsigned long long sum = 0;
        
        for (unsigned long long i = 1; i*i <= n; i++)
        {
            for (unsigned long long j = 1; j * j <= m; j++)
            {
                if (std::gcd(i, j) == 1)
                {
                    int d = i+j;
                    while (i * d <= n && j * d <= m)
                    {
                            if ((j * d * d) % (i * d + j * d) == 0)
                                sum++;
                        d += i+j;
                    }
                }
            }
        }
        cout << sum << endl;
    }
    return 0;
}

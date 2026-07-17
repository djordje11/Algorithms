#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

int ns[100000];
int ks[100000];

unsigned long long moduo = 1000000007;

unsigned long long mul(unsigned long long x, unsigned long long y)
{
    return x * y >= moduo ? (x * y) % moduo : x * y;
}
unsigned long long add(unsigned long long x, unsigned long long y)
{
    return x + y >= moduo ? (x + y) % moduo : x + y;
}
unsigned long long power_of_twos[100000];

int main()
{
    int t;

    cin >> t;

    power_of_twos[0] = 1;
    for (int i = 1; i < 100000; i++)
        power_of_twos[i] = mul(2, power_of_twos[i - 1]);


    for (int i = 0; i < t; i++)
        cin >> ns[i];

    for (int i = 0; i < t; i++)
        cin >> ks[i];


    for (int i = 0; i < t; i++)
    {
        if (ns[i] == ks[i])
            cout << 1 << endl;
        else
            cout << power_of_twos[ks[i]] << endl;
    }

    


    return 0;
}

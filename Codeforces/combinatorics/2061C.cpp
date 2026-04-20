#include <iostream>
#include <vector>
#include <map>
using namespace std;

int a[2*100000+1];
int main()
{
    int q;

    const int moduo = 998244353;
    cin >> q;

    while(q--)
    {
    int n;
    cin >> n;
    std::vector<std::map<int, unsigned long long>> mapa(n+1);
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    } 

    mapa[1][1] = 1;
    mapa[1][0] = a[1] == 0;    


    for(int i = 2; i <= n; i++)
    {
        if(i == 2)
        {
            if(a[1] == 0)
            {
                mapa[2].insert({1, 1});
            }
        }
        else
        {
            auto it = mapa[i-2].find(a[i-1]);
            if(it != mapa[i-2].end())
                mapa[i].insert({it->first+1, it->second});
        }

        auto it = mapa[i-1].find(a[i]);
        if(it != mapa[i-1].end())
        {
            auto jt = mapa[i].find(a[i]);
            if(jt == mapa[i].end())
                mapa[i].insert({it->first, it->second});
            else
                jt->second = (jt->second + it->second) % moduo;
        }
    }
    unsigned long long sum = 0;
    for(auto it : mapa[n])
        sum = (sum + it.second)% moduo;
    std::cout <<  sum  << endl;
    }
    return 0;
}

#include <cstdint>
#include <iostream>
#include <map>

using ull = unsigned long long;
using namespace std;

unsigned used;
std::map<ull, unsigned> mapa;
std::map<ull, unsigned> mapa2;

ull dp[58][58][58];

int main()
{


    for(int i = 0; i <= 57; i++)
        for(int j = 0; j <= 57; j++)
            for(int k = 0; k <= 57; k++)
                dp[i][j][k] = UINT64_MAX;


    dp[1][0][1] = 2;
    dp[0][1][1] = 2;
    dp[0][0][1] = 0;

    for(int i = 2; i <= 57; i++)
    {
        for(int x = 0; x <= 57; x++)
        {
            for(int y = 0; y <= 57; y++)
            {
                if((i+1)*i/2 < x + y)
                    continue;

                //dp[x][y][i] = UINT64_MAX;
                
                //if(dp[x][y][i-1] != 0)
                dp[x][y][i] = dp[x][y][i-1];
                
                if(x - i >= 0 && dp[x-i][y][i-1] != UINT64_MAX)
                    dp[x][y][i] = std::min(dp[x][y][i], (ull(1)<<i) + dp[x-i][y][i-1]);
                
                if(y-i >= 0 && dp[x][y-i][i-1] != UINT64_MAX)
                    dp[x][y][i] = std::min(dp[x][y][i], (ull(1)<<i) + dp[x][y-i][i-1]);
            }
        }
    }
    
    int t;
    cin >> t;
    while(t--)
    {
        ull y;
        ull x;

        cin >> x >> y;


        mapa = {};
        mapa2 = {};
        for(int i = 0; ; i++)
        {    
            mapa.insert({x>>i, i});
            if((x>>i) == 0)
                break;
        }
        for(int i = 0; ; i++)
        {
            mapa2.insert({y>>i, i});
            if((y>>i) == 0)
                break;
        }
        ull curr_min = UINT64_MAX;
        for(auto it : mapa)
        {
            auto jt = mapa2.find(it.first);
            if(jt != mapa2.end())
            {
                curr_min = std::min(curr_min, dp[it.second][jt->second][57]);
            }
        }

        if(curr_min == UINT64_MAX)
        {
            ull k = mapa[0];
            ull m = mapa2[0];

            for(ull x = k; x <= 57; x++)
                for(ull y = m; y <= 57; y++)
                {
                    curr_min = std::min(curr_min, dp[x][y][57]);
                }

        }


        cout << curr_min << endl;

    }


    return 0;
}

#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

using ull = unsigned long long ;

ull dp[300001][4];
ull att[3 * 100000 + 1];

ull dmg = 0;
ull curr_dmg = 0;

void dfs(vector<vector<int>>& graph, int curr, int par)
{    
    int childs = graph[curr].size() - (par == 0 ? 0 : 1);
    bool leaf = true;

    dp[curr][1] = dp[curr][0] = UINT32_MAX;

    for(auto it : graph[curr])
    {
        if(it != par)
        {
            leaf = false;
            dfs(graph, it, curr);
        }
    }

    if(childs > 0)
    {    
        childs+= 2;
    }
    for(ull i = 1; i <= min(childs, 20); i++)
    {
        ull sum = i * att[curr];

        for(auto it : graph[curr])
        {
            if(it != par)
            {
                ull curr_sum = dp[it][0];
                if(dp[it][2] == i)
                {
                    curr_sum = dp[it][1];
                }
                sum += curr_sum;
            }
        }

        if(sum <= dp[curr][0])
        {
            dp[curr][1] = dp[curr][0];
            dp[curr][3] = dp[curr][2];

            dp[curr][0] = sum;
            dp[curr][2] = i;
        }
        else if(sum <= dp[curr][1])
        {
            dp[curr][1] = sum;
            dp[curr][3] = i;
        }
    }


    
    if(leaf) 
    {
        dp[curr][0] = 1 * att[curr];
        dp[curr][1] = 2 * att[curr];
        dp[curr][2] = 1;
        dp[curr][3] = 2;
    }

}



int main()
{

    int t ;

    cin >> t;

    while(t--)
    {
    int n;
    cin >> n;
        dmg = 0;
        curr_dmg = 0;
    vector<vector<int>> graph(n+1);
    


    for(int i = 1; i <= n; i++)
        cin >> att[i];

    for(int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(graph, 1, 0);

    cout << dp[1][0] << endl;

}
    return 0;
}
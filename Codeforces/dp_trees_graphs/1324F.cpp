#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool colors[200001];

int dp[200001];


void dfs(vector<vector<int>>& graph, int curr, int par)
{    
    dp[curr] = colors[curr] ? 1 : -1 ;
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            dfs(graph, it, curr);

            if(dp[it] > 0)
                dp[curr] += dp[it];

        }
    }
}
void dfs2(vector<vector<int>>& graph, int curr, int par)
{    
    if(par != 0)
    {
        if(dp[curr] <= 0)
        {
            if(dp[par] >= 0)
                dp[curr] += dp[par];
        }
        else
        {
            if(dp[par] > dp[curr])
            {
                dp[curr] += dp[par] - dp[curr];
            }
        }

    }

    for(auto it : graph[curr])
    {
        if(it != par)
        {
            dfs2(graph, it, curr);
        }
    }
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> graph(n+1);

    for(int i = 1; i <= n; i++)
        cin >> colors[i];

    for(int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

 

    dfs(graph, 1, 0);
    dfs2(graph, 1, 0);


    for(int i = 1; i <= n; i++)
        cout << dp[i] << " ";
    cout << endl;

    return 0;
}
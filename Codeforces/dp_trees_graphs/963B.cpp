#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

bool dp[2 * 100000 + 1][2];


void dfs(vector<vector<int>>& graph, int curr, int par)
{
    int n = 0, m = 0;
    bool leaf = true;

    for (auto it : graph[curr])
    {
        if (it != par)
        {
            leaf = false;
            dfs(graph, it, curr);
            if (dp[it][0]) 
            {
                n++;
            }
            if (dp[it][1])
            {
                m++;
            }
        }
    }
    if (leaf)
    {
        dp[curr][0] = true;
    }
    {
        if (n % 2 == 0)
            dp[curr][0] = 1;

        if (n % 2 == 1)
            dp[curr][1] = 1;
    }
}

void dfs2(vector<vector<int>>& graph, int curr, int par)
{    
        int count = 0;
        
        for (auto it : graph[curr])
        {
            if (it != par)
            {
                if (dp[it][1])
                    dfs2(graph, it, curr);
                else
                    count++;
            }
        }

        cout << curr << endl;
        if (count > 0)
        {
            for (auto it : graph[curr])
            {
                if (it != par)
                {
                    if (dp[it][0])
                        dfs2(graph, it, curr);
                }
            }
        }
}
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int p;
        cin >> p;
        if (p != 0)
        {
            graph[i].push_back(p);
            graph[p].push_back(i);
        }
    }

    dfs(graph, 1, 0);

    cout << (dp[1][0] ? "YES":"NO") << endl;

    if (dp[1][0])
        dfs2(graph, 1, 0);

    return 0;
}

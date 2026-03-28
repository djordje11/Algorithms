#include <iostream>
#include <vector>

using namespace std;


int map[100001];
int tme = 1;
int dp[21][100001];
int cnt[100001];
int height[100001] = {-1};
#include <algorithm>
vector<vector<int>> sort_height;

void dfs(int curr, int parr, vector<vector<int>>& graph)
{
    map[curr] = tme++;
    cnt[curr] = 1;
    height[curr] = height[parr] + 1;
    sort_height[height[curr]].push_back(tme-1);
    for(auto it : graph[curr])
    {
        if(it != parr)
        {
            dfs(it, curr, graph);
            cnt[curr] += cnt[it];
        }
    } 
}

int main()
{
    int n; 
    cin >> n;
    vector<vector<int>> graph(n+1);
    sort_height = vector<vector<int>>(n+1);
    for(int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if(x > 0)
        {
            dp[0][i] = x;  
            graph[x].push_back(i);
            graph[i].push_back(x);
        }
    }

    for(int i = 1; i <= n; i++)
        if(dp[0][i] == 0)
            dfs(i, 0, graph);
    

    for(int i = 1; 1<<i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[i][j] = dp[i-1][dp[i-1][j]];



    int k;
    cin >> k;

    while(k--)
    {
        int x, p;
        cin >> x >> p;

        for(int i = 0; i <= 20; i++)
            if((1<<i) & p)
                x = dp[i][x];
        if(x == 0)
        {
            cout << 0 << endl;
            continue;
        }

        int h = height[x] + p;        
        int first = map[x];
        int last = map[x] + cnt[x] - 1;
        int count = 0;
        for(auto it : sort_height[h])
            if(it >= first && it <= last)
                count++;

        auto start = std::lower_bound(sort_height[h].begin(), sort_height[h].end(), first);
        auto end = std::upper_bound(sort_height[h].begin(), sort_height[h].end(), last);
        
        cout << int(end - start) - 1 << endl;

    }

    return 0;
}
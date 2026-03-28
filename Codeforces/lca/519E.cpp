#include <iostream>
#include <vector>


using namespace std;
int dp[21][100000 + 1]; 
int t_in[100000 + 1];
int t_out[100000 + 1];
int tme = 0;
int depth[100000 + 1] = {-1};
int cnt[100001];
int all_cnt[100001];

void dfs(int curr, int parr, vector<vector<int>>& graph)
{
    dp[0][curr] = parr;
    depth[curr] = 1 + depth[parr];
    t_in[curr] = tme++;
    cnt[curr] = 1;
    for(auto it : graph[curr])
    {
        if(it != parr)
        {
            dfs(it, curr, graph);
            cnt[curr] += cnt[it];
        }
    } 
    t_out[curr] = tme++;
}


bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n+1);

    for(int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[y].push_back(x);
        graph[x].push_back(y);
    }
    dfs(1, 0, graph);
    
    for(int i = 1; 1 << i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            dp[i][j] = dp[i-1][dp[i-1][j]];
    }

    int m;
    cin >> m;

    while(m--)
    {
        int x, y;
        cin >> x >> y;

        if(n == 1)
        {
            cout << 1 << endl;
            continue;
        }

        if(x == y)
        {
            cout << n << endl;
            continue;
        }

        if(depth[x] > depth[y])
            swap(x, y);

        if(depth[x] == depth[y])
        {
            int start_x = x;
            for(int i = 20; i >= 0; i--)
                if(dp[i][x] != 0 && !is_ancestor(dp[i][x], y))x = dp[i][x];
           
            
            for(int i = 20; i >= 0; i--)
            if(dp[i][y] != 0 && !is_ancestor(dp[i][y], start_x))y = dp[i][y];
           
            cout << n - cnt[x] - cnt[y] << endl;

            continue;
        }
        int start_x = x;
        if(!is_ancestor(x, y))
        {
            int length = 0;
            for(int i = 20; i >= 0; i--)
                if(dp[i][x] != 0 && !is_ancestor(dp[i][x], y))
                {
                    x = dp[i][x]; 
                    length = length | (1<<i);
                }
            x = dp[0][x];
            length = length + 1;
            for(int i = 20; i >= 0; i--)
                if((1<<i) & (length)) y = dp[i][y];
        }
        
        int edges = depth[y] - depth[x];
        
        if(edges % 2 == 1)
        {
            cout << 0 << endl;
            continue;
        }
        edges /= 2;
        edges--;
        for(int i = 20; i >= 0; i--)
            if((1<<i) & edges)y = dp[i][y];

        cout << cnt[dp[0][y]] - cnt[y] << endl;
    }

    return 0;
}
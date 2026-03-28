#include <climits>
#include <iostream> 
#include <vector>
#include <cmath>

using namespace std;

int dp[2 * 100000 + 1][22];
int t_in[2 * 100000 + 1];
int t_out[2 * 100000 + 1];
int qs[2 * 100000 + 1];
int depth[2 * 100000 + 1];
int tmp[2 * 100000 + 1];
int t = 0;
void dfs(int curr, std::vector<std::vector<int>>& graph, vector<int>& visited, int parr, int curr_depth)
{
    dp[curr][0] = parr;
    depth[curr] = curr_depth;
    t_in[curr] = t++;
    visited[curr] = true;
    for (auto it : graph[curr])
    {
        if (!visited[it])
            dfs(it, graph, visited, curr, curr_depth+1);
    }
    t_out[curr] = t++;
}

bool is_ancestor(int x, int y)
{
    return t_in[x] < t_in[y] && t_out[x] > t_out[y];
}

int d(int x, int y)
{
    if(x == y)
        return 0;
    if(is_ancestor(x, y) || is_ancestor(y, x))
        return std::abs(depth[x] - depth[y]);
    


    int anc = y;

    for(int i = 21; i >= 0; i--)
        if(dp[anc][i] != 0 && !is_ancestor(dp[anc][i], x))
            anc = dp[anc][i];
    
    anc = dp[anc][0];

    return depth[x] - depth[anc] + depth[y] - depth[anc];
}

int main()
{

    int n, m;
    cin >> n;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    cin >> m;
    t_out[0] = INT_MAX;
    vector<int> visited(n + 1);
    dfs(1, graph, visited, 0, 0);


    for (int i = 1; i <= 21; i++)
        for (int j = 1; j <= n; j++)
            dp[j][i] = dp[dp[j][i - 1]][i - 1];


    for (int i = 0; i < m; i++)
    {
        int x, y, a, b, k;
        cin >> x >> y >> a >> b >> k;
        

        int d1 = d(a,b);
        
        int d2 = d(a, x) + d(b, y) + 1;

        int d3 = d(b, x) + d(a, y) + 1;

        if(d1 <= k && ((k-d1) % 2) == 0)
        {
               cout <<"YES" << endl;
                continue;
        }

        if(d2 <= k && ((k-d2) % 2) == 0)
        {
               cout <<"YES" << endl;
                continue;
        }

        if(d3 <= k && ((k-d3) % 2) == 0)
        {
               cout <<"YES" << endl;
                continue;
        }

        cout << "NO" << endl;
        
    }



    return 0;
}
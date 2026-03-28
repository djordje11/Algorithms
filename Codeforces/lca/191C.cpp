#include <iostream>
#include <vector>

using namespace std;
int dp[21][2 * 100000 + 1]; 
int t_in[2*100000 + 1];
int t_out[2*100000 + 1];
int tme = 0;
int depth[2*100000 + 1] = {-1};
int count[100001];
int all_count[100001];
int edges[100000];

int cls[100001][2];
void dfs(int curr, int parr, vector<vector<pair<int,int>>>& graph)
{
    dp[0][curr] = parr;
    depth[curr] = 1 + depth[parr];
    t_in[curr] = tme++;
    for(auto it : graph[curr])
    {
        if(it.first != parr)
        {
            dfs(it.first, curr, graph);
        }
    } 
    t_out[curr] = tme++;
}
unsigned long long sum = 0;
int n;
void dfs2(int curr, int parr, vector<vector<pair<int,int>>>& graph, int id)
{
    all_count[curr] = count[curr];
    
    for(auto it : graph[curr])
    {
        if(it.first != parr)
        {
            dfs2(it.first, curr, graph, it.second);
            all_count[curr] += all_count[it.first];
            if(curr == 77972 && it.first == 26163)
            {
     //           cout << all_count[curr] << " sarke" << std::endl;
            }
            if(curr == 72089 && it.first == 77972)
            {
    //            cout << all_count[curr] << " sarke2 " << count[curr] << " " << count[it.first] << " " << all_count[it.first] << std::endl;
            }
        }
    } 
    if(n == 100000 && all_count[curr] != 0)
    {
    }
    if(parr != 0)
    {

        edges[id] = all_count[curr];
    }
}

bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}

int main()
{
    cin >> n;
    vector<vector<pair<int,int>>> graph(n+1);

    for(int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[y].push_back({x, i-1});
        graph[x].push_back({y, i-1});
    }

    dfs(1, 0, graph);
    for(int i = 1; 1 << i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            dp[i][j] = dp[i-1][dp[i-1][j]];
    }

    int k;
    cin >> k;

    int l = 0, r = 0;
    int l2 = 0, r2 = 0;
    while(k--)
    {
        int x, y;
        cin >> x >> y;
        if(depth[x] > depth[y])
            std::swap(x, y);

        int start_x = x, start_y = y;
        if(x == y)continue;

        if(is_ancestor(x, y))
        {
            count[x] -= 1;
            count[y] += 1;
            continue;
        }

        for(int i = 20; i >= 0; i--)
            if(dp[i][x] != 0 && !is_ancestor(dp[i][x], y))x = dp[i][x];
        x = dp[0][x];



        

        if(start_x == 26163)l++; 
        if(start_x == 93694)r++;

        if(start_y == 26163)l2++; 
        if(start_y == 93694)r2++;
        count[start_x] += 1;
        count[start_y] += 1;

        count[x] -= 2;
    }
    
    dfs2(1, 0, graph, -1);
    for(int i = 1; i < n; i++)
        cout << edges[i] << " ";
        cout << endl;
    return 0;
}
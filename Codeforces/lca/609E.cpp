#include <iostream>
#include <set>
#include <vector>
using namespace std;

using ull = unsigned long long;
int parent[2 * 100000 + 1];
int dp[21][2 * 100000 + 1];
int dp_max[21][2 * 100000 + 1]; 
int t_in[2*100000 + 1];
int t_out[2*100000 + 1];
int tme = 0;
int depth[2*100000 + 1] = {-1};
bool mst[2*100000 + 1];
int mst_connects[2*100000 + 1][2];
int weights[2*100000 + 1];
void dfs(int curr, int parr, vector<vector<pair<int,int>>>& graph, int w)
{
    dp[0][curr] = parr;
    dp_max[0][curr] = w;
    depth[curr] = 1 + depth[parr];
    t_in[curr] = tme++;
    for(auto it : graph[curr])
    {
        if(it.first != parr)
        {
            dfs(it.first, curr, graph, it.second);
        }
    } 
    t_out[curr] = tme++;
}

bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}

int find_parent(int node)
{
    if(parent[node] == 0)return node;
    return parent[node] = find_parent(parent[node]);
}


bool union_set(int x, int y)
{
    int xx = find_parent(x);
    int yy = find_parent(y);

    if(xx == yy)return false;
    parent[xx] = yy;
    return true;
}

int main()
{
    set<pair<int, vector<int>>> edges_sorted;
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n+1);
    for(int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        edges_sorted.insert({w, {x, y, i}});
        weights[i] = w;
        mst_connects[i][0] = x;
        mst_connects[i][1] = y;

    }
    int edges_added = 0; 
    unsigned long long mst_weight = 0;
    for(auto it : edges_sorted)
    {
        if(union_set(it.second[0], it.second[1]))
        {
            edges_added++;
            graph[it.second[0]].push_back({it.second[1], it.first});
            graph[it.second[1]].push_back({it.second[0], it.first});
            mst[it.second[2]] = true;
            mst_weight = mst_weight + ull(it.first);

        }
        if(edges_added == n-1)
            break;
    }

    dfs(1, 0, graph, 0);


    for(int i = 1; 1<<i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[i][j] = dp[i-1][dp[i-1][j]];

    for(int i = 1; 1<<i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp_max[i][j] = max(dp_max[i-1][j], dp_max[i-1][dp[i-1][j]]);    

    for(int i = 0; i < m; i++)
    {
        if(!mst[i])
        {
            int x = mst_connects[i][0];
            int y = mst_connects[i][1];

            if(depth[x] > depth[y])
                swap(x, y);

            int max_edge = 0;

            for(int i = 20; i>= 0; i--)
                if(dp[i][x] != 0 && !is_ancestor(dp[i][x],y))
                {
                    max_edge = max(max_edge, dp_max[i][x]);
                    x = dp[i][x];
                }

            if(!is_ancestor(x, y))
            {
                max_edge = max(max_edge, dp_max[0][x]);
                x = dp[0][x];
            }

            for(int i = 20; i >= 0; i--)
                if(dp[i][y] != 0 && !is_ancestor(dp[i][y], x) && dp[i][y] != x)
                {
                    max_edge = max(max_edge, dp_max[i][y]);
                    y = dp[i][y];
                }

            max_edge = max(max_edge, dp_max[0][y]);

            cout << mst_weight - ull(max_edge) + ull(weights[i]) << endl;;
        }
        else 
        {
            cout << mst_weight << endl;
    
        }
    }

    return 0;
}
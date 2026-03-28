#include <climits>
#include <iostream> 
#include <vector>

using namespace std;

int dp[2*100000 + 1][22];
int t_in[2*100000+1];
int t_out[2*100000+1];
int qs[2*100000+1];
int t = 0;
void dfs(int curr, std::vector<std::vector<int>>& graph, vector<int>& visited, int parr)
{
    dp[curr][0] = parr;
    t_in[curr] = t++;
    visited[curr] = true;
    for(auto it : graph[curr])
    {
        if(!visited[it])
            dfs(it, graph, visited, curr);
    }
    t_out[curr] = t++;
}

bool is_ancestor(int x, int y)
{
    return t_in[x] < t_in[y] && t_out[x] > t_out[y];
}
int main()
{

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n+1);

    for(int i = 0; i < n-1; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    t_out[0] = INT_MAX;
    vector<int> visited(n+1);
    dfs(1, graph, visited, 0);

    for(int i = 1; i <= 21; i++)
        for(int j = 1; j <= n; j++)
            dp[j][i] = dp[dp[j][i-1]][i-1];


    for(int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        for(int j = 0; j < k; j++)
            cin >> qs[j];

        bool can = true;
        int x = dp[qs[0]][0];

        if(k == 1)
        {
            cout << "YES" << endl;
            continue;
        }

        for(int j = 1; j < k; j++)
        {
            int parr = dp[qs[j]][0];
            if(is_ancestor(x, qs[j]) || is_ancestor(qs[j], x))
            {

            }
            else if(parr == 0 || parr == 1 || is_ancestor(parr, x) || is_ancestor(x, parr))
            {

            }
            else 
            {
                can = false;
                break;
            }
        }

        cout << (can ? "YES" : "NO") << endl;
    }
    


    return 0;
}

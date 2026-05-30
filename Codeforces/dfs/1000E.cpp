#include <iostream>
#include <vector>

using namespace std;

#define N_MAX 3*100001
using ull = signed long long;

bool visited[N_MAX];
int level[N_MAX];
int h[N_MAX];

int real_max = 0;
int num_of_bridges = 0;
int dfs(int curr,int par, vector<vector<int>>& graph, int curr_level)
{
    visited[curr] = true;
    level[curr] = curr_level;
    h[curr] = curr_level;
    int max1 = 0, max2 = 0;
    
    for(auto it : graph[curr])
    {
        if(it == par || visited[it] && level[it] > level[curr])continue;
        if(!visited[it])
        {
            int tmp = dfs(it, curr,  graph, curr_level + 1);

            if(tmp > max1)
            {
                max2 = max1;
                max1 = tmp;
            }
            else if(tmp >= max2)
            {
                max2 = tmp;
            }
        }
        h[curr] = min(h[curr], h[it]);  
    } 

    if(max1 + max2 > real_max)
        real_max = max1 + max2;
    if(h[curr] > level[par])
    {   
        max1++;
    }
    return max1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1);

    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1, 0, graph, 0);
    cout << real_max << endl;

    return 0;
}

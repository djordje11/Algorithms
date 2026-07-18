#include <iostream>
#include <vector>

using namespace std;

#define N_MAX 5*100001
using ull = signed long long;

bool visited[N_MAX];
int parent[N_MAX];
int level[N_MAX];


void dfs2(int curr,int par, vector<vector<int>>& graph, vector<int>& unpaired, vector<pair<int, int>>& paired, int curr_level)
{
    visited[curr] = true;
    bool curr_paired = false;
    parent[curr] = par;
    level[curr] = curr_level;
    if(unpaired.size() > 0)
    {
        curr_paired = true;
        int x = unpaired.back();
        unpaired.pop_back();

        paired.push_back({x, curr});
    }
    for(auto it : graph[curr])
    {
        if(!visited[it])
        {
            dfs2(it, curr, graph, unpaired, paired, curr_level+1);
        }
    }

    if(!curr_paired)
        unpaired.push_back(curr);
}
int main()
{
    int t;

    cin >> t;

    while(t--)
    {
        int n, m;
        cin >> n >> m;

        for(int i = 1; i <= n; i++)
            level[i] = visited[i] = parent[i] = 0;

        vector<vector<int>> graph(n+1);

        for(int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        vector<int> unpaired; vector<pair<int, int>> paired;
        dfs2(1, 0, graph, unpaired, paired, 0);
      
        if(unpaired.size() >= n/2 + n%2)
        {
            int max = 0;
            int node = 0;
            for(auto it : unpaired)
            {
                if(level[it] > max)
                {
                    max = level[it];
                    node = it;
                }
            }
            cout << "PATH" << "\n";
            cout << max+1 << "\n";
            while(node != 0)
            {
                cout << node << " ";
                node = parent[node];
            }

        }
        else 
        {
            cout << "PAIRING" << "\n";
            cout << paired.size() << "\n";
            for(auto it : paired)
                cout << it.first << " " << it.second << "\n";
        }

    }
    

    return 0;
}

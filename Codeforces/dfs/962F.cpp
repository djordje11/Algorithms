#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define N_MAX 100001

bool visited[N_MAX];
int level[N_MAX];
int h[N_MAX];
map<pair<int, int>, int> edges_map;
int edges_cycles[N_MAX];
int cycle_type[N_MAX];
int cycle_cord[N_MAX][2];
int cyc_id = 1;

int t_in[N_MAX];
int t_out[N_MAX];

int parrent[N_MAX];
int t = 0;

void dfs1(int curr,int par, vector<vector<int>>& graph)
{
    t_in[curr] = t++;
    visited[curr] = true;
    parrent[curr] = par;
    for(auto it : graph[curr])
    {
        if(!visited[it])
        {
            dfs1(it, curr, graph);
        }
    } 
    t_out[curr] = t++;
}

bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}

void dfs(int curr,int par, vector<vector<int>>& graph, int curr_level)
{
    visited[curr] = true;
    level[curr] = curr_level;
    h[curr] = curr_level;
    for(auto it : graph[curr])
    {
        if(it == par)continue;

        bool found = false;
        if(visited[it] && level[it] < level[curr])
        {
            int x = curr;
            int y = it;
            if(x > y)swap(x, y);
            auto jt = edges_map[{x,y}];
            edges_cycles[jt] = cyc_id;

            int tmp = curr;

            while(is_ancestor(it, tmp))
            {
                int x = tmp;
                int y = parrent[tmp];
                if(x > y)swap(x, y);

                auto zt = edges_map[{x,y}];

                if(edges_cycles[zt] == 0)
                {
                    edges_cycles[zt] = cyc_id;
                    tmp = parrent[tmp];
                }
                else 
                {
                    found = true;
                    cycle_type[edges_cycles[zt]] = 2;
                    tmp = cycle_cord[edges_cycles[zt]][0];
                }
            }
            if(found)
            {
                cycle_type[cyc_id] = 2;
            }
            else {
                cycle_type[cyc_id] = 1;
            }
            cycle_cord[cyc_id][0] = it;
            cycle_cord[cyc_id++][1] = curr;

        }
        if(!visited[it])
        {
            dfs(it, curr,  graph, curr_level + 1);
        }
        h[curr] = min(h[curr], h[it]);  
    } 
    return;
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

        if(x > y)swap(x, y);
        edges_map.insert({{x, y}, i});
    }

    for(int i =  1; i <= n; i++)
        if(!visited[i])
            dfs1(i, 0, graph);

    for(int i = 1; i <= n; i++)
        visited[i] = false;

    for(int i =  1; i <= n; i++)
        if(!visited[i])
            dfs(i, 0, graph, 0);
   
    std::set<int> res;
    for(int i = 0; i < m; i++)
    {
        if(cycle_type[edges_cycles[i]] == 1)
            res.insert(i+1);
    }

    cout << res.size()<< endl;

    for(auto it : res)
        cout << it << " ";
    cout << endl;

    return 0;
}

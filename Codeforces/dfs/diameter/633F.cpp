#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define N_MAX 100001
using ull = signed long long;

ull ch[N_MAX];

ull max_dist = 0;
ull max_node = 0;
set<int> set_path;
vector<int> path;
ull dist[N_MAX];
ull visited[N_MAX];
void dfs(int curr,int par, vector<vector<int>>& graph,  ull dist, bool count)
{
    visited[curr] += count;
    if(dist > max_dist)
    {
        max_dist = dist;
        max_node = curr;
    }
    for(auto it : graph[curr])
    {
        if(it != par && set_path.count(it) == 0)
        {
            dfs(it, curr,  graph, dist + ch[it], count);

        }
    } 
}
bool found;
void dfs2(int curr,int par, vector<vector<int>>& graph,  int dest)
{
    path.push_back(curr);
    if(curr == dest)
    {
        found = true;
        return ;
    }
    for(auto it : graph[curr])
    {
        if(it!= par )
        {
            dfs2(it, curr,  graph, dest);
            if(found)return;
        }
    } 
    if(!found)
    {
        path.pop_back();
    }
    return;
}




int main()
{
    int n, m;
    cin >> n;
    m = n-1;

    for(int i = 1; i <= n; i++)
        cin >> ch[i];

    vector<vector<int>> graph(n+1);
    map<pair<int, int>, int> edges;
    vector<int> distances(n+1);
    
    for(int i = 0; i < n-1; i++)
    {
        int x, y, w;
        cin >> x >> y;
        graph[x].push_back(y );
        graph[y].push_back(x);
    }
    dfs(1, 0, graph, ch[1], false);

    int diameter_a = max_node;

    max_dist = 0;
    max_node = 0;
    dfs(diameter_a, 0, graph, ch[diameter_a], false);

    int diameter_b = max_node;
    dfs2(diameter_a, 0, graph, diameter_b);

    ull sum = 0;
    for(auto it : path)
    {
        sum += ch[it];
        set_path.insert(it);
    }

    for(int i = 1; i <= n; i++)
    {
        if(set_path.count(i) == 1)
        {
            max_dist = 0;
            max_node = 0;
            dfs(i, 0, graph, ch[i], false);
            dist[i] = max_dist;
        }
    }

    ull second_max = 0;
    for(int i = 1; i <= n; i++)
    {
        if(set_path.count(i) == 0 && visited[i] == 0)
        {
            max_dist = 0;
            max_node = 0;
            dfs(i, 0, graph, ch[i], true);
            int tmp = max_node;
            max_dist = 0;
            max_node = 0;
            
            dfs(tmp, 0, graph, ch[tmp], true);
            second_max = max(second_max, max_dist);
        }
    }

    ull max1 = sum + second_max;
    for(int i = 0; i < path.size()-1; i++)
    {
        max1 = max(max1, sum + dist[path[i]] + dist[path[i+1]] - ch[path[i]] - ch[path[i+1]]);
    }

    ull max_g = 0;
    ull left_to_diameter = 0;

    for(int i = 1; i < path.size()-1; i++)
    {
        max_g = max(max_g, dist[path[i-1]] + left_to_diameter);
        left_to_diameter += ch[path[i-1]];

        max1 = max(sum - left_to_diameter + dist[path[i]] - ch[path[i]] + max_g, max1);
    }

    max_g = 0;
    ull right_to_diameter = 0;
    for(int i = path.size()-2; i >= 1; i--)
    {
        max_g = max(max_g, dist[path[i+1]] + right_to_diameter);
        right_to_diameter += ch[path[i+1]];

        max1 = max(sum - right_to_diameter + dist[path[i]] - ch[path[i]] + max_g, max1);
    }

    cout << max1 << endl;


    return 0;
}

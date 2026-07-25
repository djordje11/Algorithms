#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define N_MAX 100001
using ull = signed long long;

bool visited[N_MAX];
int level[N_MAX];
int h[N_MAX];

int max_dist = 0;
int max_node = 0;
set<int> set_path;

void dfs(int curr,int par, vector<vector<pair<int, int>>>& graph,  int dist)
{
    if(dist > max_dist)
    {
        max_dist = dist;
        max_node = curr;
    }
    for(auto it : graph[curr])
    {
        if(it.first != par && set_path.count(it.first) == 0)
        {
            dfs(it.first, curr,  graph, dist + it.second);

        }
    } 
}

vector<int> path;
bool found = false;

void dfs2(int curr,int par, vector<vector<pair<int, int>>>& graph,  int dest)
{
    path.push_back(curr);
    if(curr == dest)
    {
        found = true;
        return ;
    }
    for(auto it : graph[curr])
    {
        if(it.first != par )
        {
            dfs2(it.first, curr,  graph, dest);
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
    int n, m, k;
    cin >> n >> k;
    m = n-1;
    vector<vector<pair<int, int>>> graph(n+1);
    map<pair<int, int>, int> edges;
    vector<int> distances(n+1);
    for(int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        graph[x].push_back({y, w});
        graph[y].push_back({x, w});

        if(x > y)swap(x, y);
        edges.insert({{x, y}, w});
    }
    dfs(1, 0, graph, 0);

    int diameter_a = max_node;

    max_dist = 0;
    max_node = 0;
    dfs(diameter_a, 0, graph, 0);

    int diameter_b = max_node;
    dfs2(diameter_a, 0, graph, diameter_b);

    for(auto it : path)
    {
        set_path.insert(it);
    }


    for(auto it : path)
    {
        max_dist = 0;
        max_node = 0;

        dfs(it, 0, graph, 0);
        distances[it] = max_dist;
    }

    map<int, int> ds;
    
    for(int i = 1; i < k-1 && i < path.size()-1; i++)
    {
        auto it = ds.find(distances[path[i]]);

        if(it == ds.end())
        {
            ds.insert({distances[path[i]], 1});
        }
        else {
            it->second++;
        }
    }

    int dist_right = 0;
    int dist_left = 0;


    for(int i = k; i < path.size(); i++)
    {
        int x = path[i-1];
        int y = path[i];
        if(x > y)swap(x, y);

        dist_right += edges[{x, y}];
    }

    auto it = ds.find(dist_right);

    if(it == ds.end())
    {
        ds.insert({dist_right, 1});
    }
    else {
        it->second++;
    }


     it = ds.find(dist_left);

    if(it == ds.end())
    {
        ds.insert({dist_left, 1});
    }
    else 
    {
        it->second++;
    }

    int min1 = ds.rbegin()->first;
    int p_n = path.size();
  
    for(int i = 1; i <= p_n-k; i++)
    {
        ds[dist_left]--;
        if(ds[dist_left] == 0)
        {
            ds.erase(dist_left);
        }

        if(k > 2 && p_n > 2)
        {
            ds.erase(distances[path[i]]);
        }

        int x = path[i-1];
        int y = path[i];
        if(x > y)swap(x, y);

        dist_left += edges[{x, y}];

        auto it = ds.find(dist_left);
        if(it == ds.end())
        {
            ds.insert({dist_left, 1});
        }
        else {
            it->second++;
        }

        x = path[i-2+k];
        y = path[i-1+k];

        ds[dist_right]--;
        if(ds[dist_right] == 0)
        {
            ds.erase(dist_right);
        }

        if(k > 2 && p_n > 2)
        {
            auto it = ds.find(distances[path[i+k-2]]);
            if(it == ds.end())
            {
                ds.insert({distances[path[i+k-2]], 1});
            }
            else {
                it->second++;
            }
        }

        if(x > y)swap(x, y);

        dist_right -= edges[{x, y}];
        it = ds.find(dist_right);
        if(it == ds.end())
        {
            ds.insert({dist_right, 1});
        }
        else {
            it->second++;
        }
        min1 = min(min1, ds.rbegin()->first);
    }
    cout << min1 << endl;
    return 0;
}

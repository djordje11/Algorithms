#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
using namespace std;
 
#define MAX_N 501
using ull = unsigned long long;

int dist[MAX_N];
 
ull graph[MAX_N][MAX_N];
ull graph_reverse[MAX_N][MAX_N];
ull blocking_flow[MAX_N][MAX_N];
ull entering[MAX_N];
ull leaving[MAX_N];

vector<vector<int>> adj;
 
int top_sort[MAX_N];
int last_pushed[MAX_N];
bool frozen[MAX_N];
bool acc[MAX_N];

 
vector<vector<int>> level_graph(int n)
{
    queue<int> bfs;
 
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INT32_MAX;
        top_sort[i] = 0;
        leaving[i] = entering[i] = 0;
        last_pushed[i] = 0;
        acc[i] = frozen[i] = false;
    }
    bfs.push(1);
    dist[1] = 0;
 
 
    vector<vector<int>> ret_graph(n + 1);
    while (!bfs.empty())
    {
        int curr = bfs.front();
        bfs.pop();
        for (auto it : adj[curr])
        {
            if ((graph_reverse[curr][it] > 0 || graph[curr][it] > 0))
            {
                if (dist[curr] + 1 == dist[it])
                {
                    ret_graph[curr].push_back(it);
                    top_sort[it]++;
                }
                else if (dist[curr] + 1 < dist[it])
                {
                    dist[it] = dist[curr] + 1;
                    bfs.push(it);
                    ret_graph[curr].push_back(it);
                    top_sort[it]++;
                }
            }
        }
    }
 
    return ret_graph;
}
 
void find_blocking_flow(vector<vector<int>> graph_l, int n)
{
    static int ind = 0;
    ind++;
    vector<vector<pair<int, ull>>> edges_entering(n + 1);
    static int active[MAX_N];
    int num_of_active = 0;
 
    queue<int> next;
    for (auto it : graph_l[1])
    {
        active[num_of_active++] = it;
        entering[it] = graph[1][it] + graph_reverse[1][it];
        blocking_flow[1][it] = entering[it];
        edges_entering[it].push_back({ 1, graph[1][it] + graph_reverse[1][it] });
      
        if (top_sort[it] == 1)
        {
            next.push(it);
        }
    }
    bool track_push = false;
    stack<int> actives;
    while (true)
    {
        //push phase
        while (!next.empty())
        {
            int curr = next.front();
            next.pop();

            if(curr == n || acc[curr])continue; 

            for (int& i = last_pushed[curr]; i < graph_l[curr].size() && entering[curr] > leaving[curr]; i++)
            {
                auto it = graph_l[curr][i];

                if(frozen[it])
                    continue;

                ull dif = entering[curr] - leaving[curr]; 
                ull capacity = graph[curr][it] + graph_reverse[curr][it];
 
                if(blocking_flow[curr][it] < capacity)
                {
                    ull v = min<ull>(dif, capacity - blocking_flow[curr][it]);
                    edges_entering[it].push_back({ curr, v });
                    leaving[curr] += v;
                    entering[it] += v;

                    blocking_flow[curr][it] += v;
                    next.push(it);
                }
 
                if(blocking_flow[curr][it] < capacity)
                {
                    break;
                }
            }

            if(entering[curr] > leaving[curr])
            {
                acc[curr] = true;
                actives.push(curr);
            }        
        }
 
        //rebalance phase
        if(actives.size() == 0)
            break;
        int iter = 0;
 
        int initial_dist = dist[actives.top()];
        int curr;

        while(actives.size() > 0 && dist[curr = actives.top()] == initial_dist)
        {
            actives.pop();

            if(!frozen[curr])
            {
                frozen[curr] = true;
                while(entering[curr] != leaving[curr])
                {
                    auto it = edges_entering[curr].back();
                    ull diff = min(entering[curr] - leaving[curr], it.second);
                    it.second -= diff;

                    entering[curr] -= diff;
                    leaving[it.first] -= diff;

                    blocking_flow[it.first][curr] -= diff;
                        
                    if(it.first != 1 && !acc[it.first])
                        next.push(it.first);

                    if(it.second == 0)
                        edges_entering[curr].pop_back();            
                }
            }
        }
    }
}
 
int main()
{ 
    int n, m, x;
    cin >> n >> m;

    adj = vector<vector<int>>(n + 1);
  
    for (int i = 0; i < m; i++)
    {
        int x, y, c ;
        cin >> x >> y >> c;
 
        if (graph[x][y] == 0 && graph[y][x] == 0)
        {
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
 
        graph[x][y] += c;
    }
 
    bool end = false;
    while(!end)
    {
        auto g = level_graph(n);
        find_blocking_flow(g, n);
        
        end = true;

        for(int i = 1; i < g.size(); i++)
            for(auto j : g[i])
            {
                ull v = blocking_flow[i][j];
                if(v > 0) end = false;
                ull diff = min(v, graph[i][j]);
                v -= diff;
                graph[i][j] -= diff;
                graph_reverse[j][i] += diff;
                blocking_flow[i][j] = 0;
                if(v > 0)
                {
                    graph_reverse[i][j] -= v;
                    graph[j][i] += v;
                }
 
            }
    }
 
    ull sum = 0;
    for(int i = 2; i <=n; i++)
        sum += graph_reverse[i][1];
 
    cout << sum << endl;
 
    return 0;
}

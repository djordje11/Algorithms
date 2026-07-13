#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
using namespace std;
 
#define MAX_N 110
using ull = unsigned long long;

int dist[MAX_N];
 
map<pair<int, int>, ull> graph;
ull graph_reverse[MAX_N][MAX_N];
ull blocking_flow[MAX_N][MAX_N];
ull entering[MAX_N];
ull leaving[MAX_N];

vector<vector<int>> adj;
 
int top_sort[MAX_N];
int last_pushed[MAX_N];
bool frozen[MAX_N];
bool acc[MAX_N];

 
double diff = 0.00000001;
unsigned long long const_graph[MAX_N][MAX_N];

vector<vector<int>> const_adj;

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
            if ((graph_reverse[curr][it] > 0 || graph[{curr, it}] > 0))
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
 
 
        entering[it] = graph[{1, it}] + graph_reverse[1][it];
        blocking_flow[1][it] = entering[it];
        edges_entering[it].push_back({ 1, graph[{1,it}] + graph_reverse[1][it] });
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
                ull capacity = graph[{curr,it}] + graph_reverse[curr][it];
 
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

#include <iomanip>
ull dinic()
{
    bool end = false;
    int n = adj.size() - 1;
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
                ull diff = min(v, graph[{i,j}]);
                v -= diff;
                graph[{i,j}] -= diff;
                graph_reverse[j][i] += diff;
                blocking_flow[i][j] = 0;
                if(v > 0)
                {
                    graph_reverse[i][j] -= v;
                    graph[{j,i}] += v;
                }
 
            }
    }
 
    ull sum = 0;
    for(int i = 2; i <=n; i++)
        sum += graph_reverse[i][1];
 
    return sum;
}


int a[100];
int main()
{
    int  n;
    cin >> n;
    ull  max1 = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        max1 = max(max1, ull(std::abs(-a[i])));
    }

    adj = vector<vector<int>>(n+3);

    for(int i = 2; i <= n+1; i++)
    {
        //graph[1][i] = max1;
        graph.insert({{1, i}, max1});
        adj[1].push_back(i);
        adj[i].push_back(1);

        //graph[i][n+2] = max1 - a[i-2];
        graph.insert({{i, n+2}, max1 - a[i-2]});
        adj[i].push_back(n+2);
        adj[n+2].push_back(i);
    }


    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            if(i % j == 0)
            {
                //graph[i+1][j+1] = ull(1) << 31;
                graph.insert({{i+1, j+1}, ull(1) << 31});
                adj[i+1].push_back(j+1);
                adj[j+1].push_back(i+1);
            }
        }
    }

    cout << ull(n) * max1 - dinic() << endl;

    return 0;
}

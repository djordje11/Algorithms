#include <iostream>
#include <queue>
#include <vector>
#include <stack>

int dp[101][101];
int ships[1001][3];
int bases[1001][2];
int dist[2003];

using namespace std;

#define MAX_N 2003

int graph_reverse[MAX_N][MAX_N];

vector<vector<int>> adj;
 
int top_sort[MAX_N];
int last_pushed[MAX_N];
bool frozen[MAX_N];
bool acc[MAX_N];
using ull = unsigned long long;
ull graph[2003][2003];

ull blocking_flow[MAX_N][MAX_N];
ull entering[MAX_N];
ull leaving[MAX_N];

vector<vector<int>> level_graph(int n)
{
    queue<int> bfs;
 
    for (int i = 1; i <= n; i++)
    {
        dist[i] = 200;
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

int dinic()
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
                ull diff = std::min(v, graph[i][j]);
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
 
    return sum;
}


int main()
{
    int n, m;
    cin >> n >> m;


    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[i][j] = 200;

    for(int i = 1; i <= n; i++)
        dp[i][i] = 0;
    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        dp[y][x] = dp[x][y] = 1;
    }


    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            for(int k = 1; k <= n; k++)
            {
                dp[j][k] = min(dp[j][k], dp[j][i] + dp[i][k]); 
            }
        }
    }

    ull s, b, k, h;
    cin >> s >> b >> k >> h;


    for(int i = 1; i <= s; i++)
    {
        cin >> ships[i][0] >> ships[i][1] >> ships[i][2]; 
    }

    for(int i = 1; i <= b; i++)
    {
        cin >> bases[i][0] >> bases[i][1]; 
    }

    adj = vector<vector<int>>(3+s+b);
    for(int i = 1; i <= s; i++)
    {
        graph[1][i+1] = 1;
        adj[1].push_back(i+1);
        adj[i+1].push_back(1);

        for(int j = 1; j <= b; j++)
        {
            if(dp[ships[i][0]][bases[j][0]] <= n && dp[ships[i][0]][bases[j][0]] <= ships[i][2] && ships[i][1] >= bases[j][1])
            {
                
                if(graph[i+1][s+1+j] == 0)
                {
                    adj[i+1].push_back(s+1+j);
                    adj[s+1+j].push_back(i+1);
                    
                }
                graph[i+1][s+1+j] = 1;


                if(graph[s+1+j][2+b+s] == 0)
                {
                    adj[2+b+s].push_back(s+1+j);
                    adj[s+1+j].push_back(2+b+s);
                }
                graph[s+1+j][2+b+s] = 1;


            }
        }
    }

    int flow = dinic();
    cout  << min(s*h, flow*k) << endl;
    return 0;
}



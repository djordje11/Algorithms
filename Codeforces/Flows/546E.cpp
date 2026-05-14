#include <iostream>

using namespace std;

int a[102];
int b[102];

#include <cstdint>
#include <iostream>
#include <queue>
 
 
#define MAX_N 501

int previous[MAX_N];
int min_edge[MAX_N];
bool visited[MAX_N];
int graph[MAX_N][MAX_N];
int graph_reverse[MAX_N][MAX_N];

int max_flow(int n)
{
    bool found = true; 
    while(found)
    {
        found = false;
        for(int i = 1; i <= n; i++)
            visited[i] = previous[i] = visited[i] = false;
 
        queue<int> bfs;
        visited[1] = true;
        min_edge[1] = INT32_MAX;
        bfs.push(1);

        while(!bfs.empty())
        {
            int curr = bfs.front();
            bfs.pop();
            for(int i = 1; i <= n; i++)
            {
                if( (graph_reverse[curr][i] > 0|| graph[curr][i] > 0) && !visited[i])
                {
                    previous[i] = curr;
                    min_edge[i] = min(min_edge[curr], abs(max(graph[curr][i], graph_reverse[curr][i])));
                    bfs.push(i);
                    visited[i] = true;
                    if(i == n)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }
        
        if(found)
        {
            int y = n;
            while(y != 1)
            {
                int x = previous[y];
                if(graph[x][y] >= min_edge[n])
                {
                    graph[x][y] -= min_edge[n];
                    graph_reverse[y][x] += min_edge[n];
                }
                else
                {
                    graph_reverse[x][y] -= min_edge[n];
                    graph[y][x] += min_edge[n];   
                }
                y = x;
            }
        }
    }
    return 0;
}

int edges[200][2];
int main()
{
    int n, m;
    cin >> n >> m;
    
    int sum1 = 0, sum2 = 0;
    for(int i = 1; i <= n; sum1+=a[i], i++)
        cin >> a[i];
    
    for(int i = 1; i <= n; sum2+=b[i], i++)
        cin >> b[i];
    
    if(sum1 != sum2)
    {
        cout << "NO" << endl;
        return 0;
    }

    for(int i = 0; i < m; i++)
        cin >> edges[i][0] >> edges[i][1];


    for(int i = 1; i <= n; i++)
    {
        graph[1][2*i] = a[i];
        graph[2*i][2*i+1] = a[i];
        graph[2*i+1][2*n+2] = b[i];
        
        for(int j = 0; j < m; j++)
        {
            if(edges[j][0] == i || edges[j][1] == i)
            {
                int other = edges[j][0] != i ? edges[j][0] : edges[j][1];
                graph[2*i][2*other + 1] = a[i];
            }
        }
    }

    max_flow(2*n + 2);

    int flow = 0;
    for(int i = 1; i <= 2*n+1; i++)
    {
        flow += graph_reverse[i][1];
    }

    if(flow != sum1)
    {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(i == j)cout << graph_reverse[2*i+1][2*i] << " ";
            else cout << graph_reverse[2*j+1][2*i] << " ";
        }
        cout << endl;
    }

    return 0;
}

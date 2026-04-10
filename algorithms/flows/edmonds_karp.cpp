// max flow is in sum (graph[1][i]) where  1 <= i <= n

#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
using namespace std;
 
 
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

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int x, y, c;
        cin >> x >> y >> c;
        graph[x][y] = c;
    }
    max_flow( n); 
    return 0;
}

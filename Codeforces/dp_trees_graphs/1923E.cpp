#include <iostream>
#include <vector>

long long unsigned current_path_colors[2*100000 + 1];

long long unsigned sum = 0;
void dfs(int node, std::vector<std::vector<int>>& graph, int* colors, std::vector<bool>& visited)
{
    visited[node] = true;
    long long unsigned tmp = current_path_colors[colors[node]];
    sum += current_path_colors[colors[node]];

    for(auto it : graph[node])
    {
        if(visited[it])continue;
        current_path_colors[colors[node]] = 1;
        long long unsigned tmp2 = current_path_colors[colors[it]];
        dfs(it, graph, colors, visited);
        current_path_colors[colors[it]] = tmp2+1;
    }

    current_path_colors[colors[node]] = 1;
}

int main()
{
    int t;
    std::cin >> t;
    while(t--)
    {

    
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n+1);
    std::vector<bool> visited(n+1, false);
    int colors[2 * 100000 + 1];
    int x, y;

    for(int i = 1; i <= n; i++)
        std::cin >> colors[i];

    for(int i = 0; i < n-1; i++)
    {
        std::cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for(int j = 1; j <= n; j++)
        current_path_colors[j] = 0;    
    sum = 0;
    dfs(1, graph, colors, visited);
    std::cout << sum << std::endl;
    }
    return 0;
}

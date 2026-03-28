#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

int parent[100001];
bool visited[100001];
bool edge_in_mst[200001];
//int weights[500001][3];
int find_parent(int x)
{
    if (parent[x] == 0)return x;
    return parent[x] = find_parent(parent[x]);
}
 
bool dsu(int x, int y)
{
    int px = find_parent(x);
    int py = find_parent(y);
 
    if (py == px)return false;
 
    parent[px] = py;
    return true;
}
void dfs(int curr, int parr, vector<set<pair<int, int>>>& graph)
{
    for(auto it : graph[curr])
    {
        if(it != parr)
        {
            dfs(it, curr, graph);
        }
    } 
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<set<pair<int, int>>> graph(n+1);



    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].insert({i+1, y});
        graph[y].insert({i+1, x});
        edge_in_mst[i+1] = dsu(x, y);
    }


    return 0;
}
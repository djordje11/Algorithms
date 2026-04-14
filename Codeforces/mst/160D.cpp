// CF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include <limits>
#include <map>
#include <vector>
#include <set>

using namespace std;

#define N_MAX 100001
#define M_MAX 100001

int t_in[N_MAX];
bool visited[N_MAX];
int in_cycle[M_MAX];

int parent[100001];
int graph_mapping[100001];

int tme = 1;

int dfs(int curr, int parr, vector<vector<pair<int, int>>>& graph)
{
    t_in[curr] = tme++;
    visited[curr] = true;
    int min_t_in = INT32_MAX;

    for (auto it : graph[curr])
    {
        if (!visited[it.first])
        {
            int ret = dfs(it.first, curr, graph);
            min_t_in = min(min_t_in, ret);
            if (ret <= t_in[curr])
            {
                in_cycle[it.second] = true;
            }
        }
        else if (it.first != parr)
        {
            if (t_in[it.first] < min_t_in)
            {
                min_t_in = t_in[it.first];
            }
            in_cycle[it.second] = true;
        }
    }
    return min_t_in;
}


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

int main()
{
    int n, m;
    cin >> n >> m;

    map<int, vector<vector<int>>> mapa;

    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;

        auto it = mapa.find(w);
        if (it == mapa.end())
        {
            mapa.insert({ w , {{x,y,i}} });
        }
        else
            it->second.push_back({ x, y, i });
    }

    for (auto it : mapa)
    {
        int count = 1;
        set<int> map_edges;
        vector<vector<pair<int, int>>> graph(1);
        map<pair<int, int>, int> maping_edges;
        int m_e = 0;
        for (auto edge = it.second.begin(); edge != it.second.end(); edge++)
        {
            int x = (*edge)[0];
            int y = (*edge)[1];
            int pos = (*edge)[2];
            int px = find_parent(x);
            int py = find_parent(y);

            if (px != py)
            {

                if (!map_edges.count(px))
                {
                    graph.push_back({});
                    visited[count] = false;
                    graph_mapping[px] = count++;
                    map_edges.insert(px);
                }
                if (!map_edges.count(py))
                {
                    visited[count] = false;
                    graph.push_back({});
                    graph_mapping[py] = count++;
                    map_edges.insert(py);
                }

                auto find_edge_it = maping_edges.find({ px, py });
                if (find_edge_it != maping_edges.end())
                {
                    in_cycle[pos] = 1;
                    in_cycle[find_edge_it->second] = 1;
                }
                else
                {
                    graph[graph_mapping[py]].push_back({ graph_mapping[px], pos });
                    graph[graph_mapping[px]].push_back({ graph_mapping[py],  pos });
                    maping_edges.insert({ {px, py}, pos });
                    maping_edges.insert({ {py, px}, pos });
                }
            }
            else
            {
                in_cycle[pos] = 2;
            }
        }

        tme = 1;
        if(graph.size() > 1)
            dfs(1, 0, graph);
        for (auto edge = it.second.begin(); edge != it.second.end(); edge++)
            dsu((*edge)[0], (*edge)[1]);

    }

    for (int i = 0; i < m; i++)
        if (in_cycle[i] == 0)
            cout << "any" << endl;
        else if (in_cycle[i] == 1)
            cout << "at least one" << endl;
        else
            cout << "none" << endl;
    return 0;
}

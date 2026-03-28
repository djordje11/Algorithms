#include <iostream>
#include <map>
#include <vector>

using namespace std;

int parent[200001];

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

    map<int, vector<pair<int, int>>> edges;
    for(int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;

        auto it = edges.find(w);

        if(it == edges.end())
        {
            edges.insert({w, {{x, y}}});
        }
        else 
        {
            it->second.push_back({x, y});
        }
    }


    int sum = 0;
    for(auto it : edges)
    {
        int can_into_mst = 0;
        for(auto jt : it.second)
        {
            if(find_parent(jt.first) != find_parent(jt.second))
                can_into_mst++;
        }

        int inserted_into_mst = 0;
        for(auto jt : it.second)
        {
            inserted_into_mst += dsu(jt.first, jt.second);
        }
        sum += can_into_mst - inserted_into_mst;
    }
    std::cout << sum << std::endl;



    return 0;
}
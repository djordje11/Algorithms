#include <iostream>
#include <map>
#include <vector>
#include <chrono>

using namespace std;

int parent[500001];
bool can[500001];
int weights[500001][3];

int find_parent(int x)
{
    if (parent[x] == 0)return x;
    return parent[x] = find_parent(parent[x]);
}
int find_parent_2(int x)
{
    while(parent[x] != 0)x = parent[x];
    return x;
}

 
bool dsu(int x, int y)
{
    int px = find_parent(x);
    int py = find_parent(y);
 
    if (py == px)return false;
 
    parent[px] = py;
    return true;
}
 
int xs[500001];
std::map<int, vector<int>> trees[500001];
bool can_mst[500001];
#include <set>
std::set<int> sorted_weights;
int main()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++)
    {
        cin >> weights[i][0] >> weights[i][1] >> weights[i][2];
        sorted_weights.insert(weights[i][2]);
    }
    
    int q;
    cin >> q;

    for(int i = 0; i < q; i++)
    {
        int k;
        cin >> k;
        can_mst[i] = true;
        for(int j = 0; j < k; j++)
        {   
            int x;
            cin >> x;
            x--; 
            int w = weights[x][2];
            auto it = trees[i].find(w);

            if(it == trees[i].end())
            {
                trees[i].insert({w, {x}});
            }
            else 
            {
                it->second.push_back(x);
            }

        }
    }









    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[ns]" << std::endl;
    
    return 0;
}
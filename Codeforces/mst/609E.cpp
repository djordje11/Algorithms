#include <iostream>
#include <set>
#include <vector>
#include <map>

using namespace std;

using ull = unsigned long long;
int parent[2 * 100000 + 1];
int dp[21][2 * 100000 + 1];
int dp_max[21][2 * 100000 + 1]; 
int t_in[2*100000 + 1];
int t_out[2*100000 + 1];
int tme = 0;
int depth[2*100000 + 1] = {-1};
int mst[2*100000 + 1];
int mst_connects[2*100000 + 1][2];
int weights[2*100000 + 1];


int find_parent(int node)
{
    if(parent[node] == 0)return node;
    return parent[node] = find_parent(parent[node]);
}


bool union_set(int x, int y)
{
    int xx = find_parent(x);
    int yy = find_parent(y);

    if(xx == yy)return false;
    parent[xx] = yy;
    return true;
}


int main()
{
    //std::set<pair<int, vector<int>>> edges_sorted;
    
    std::map<int, vector<int>> edges_sorted;
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;

        auto it = edges_sorted.find(w);
        if(it == edges_sorted.end())
        {
            edges_sorted.insert({w, {i}});
        }
        else 
        {
            it->second.push_back(i);
        }

        mst_connects[i][0] = x;
        mst_connects[i][1] = y;
    }

    unsigned long long mst_weight = 0;

    for(auto it : edges_sorted)
    {
        map<pair<int, int>, vector<int>> count;
        for(auto jt : it.second)
        {
            int x = find_parent(mst_connects[jt][0]);
            int y = find_parent(mst_connects[jt][1]);

            if(x > y)
                swap(x, y);

            if(x == y)
            {
                // None
                mst[jt] = 1;
            }
            else 
            {
                auto zt = count.find({x, y});
                if(zt == count.end())
                {
                    count.insert({{x, y}, {jt}});
                }
                else 
                {
                    zt->second.push_back(jt);
                }

            }
        }
        
        for(auto jt : count)
        {
            bool any = jt.second.size() > 1;
            if(any)
            for(auto zt : jt.second)
            {
                mst[zt] = 2;
            }
        }

        for(auto jt : it.second)
        {
            int x = find_parent(mst_connects[jt][0]);
            int y = find_parent(mst_connects[jt][1]);

            union_set(x, y);
        }
    }


    for(int i = 0; i < m; i++)
    if(mst[i] == 0)cout << "any" << endl;
    else if(mst[i] == 1)
        cout << "none" << endl;
    else
        cout << "at least one" << endl;
        
 
    cout << endl;

    return 0;
}

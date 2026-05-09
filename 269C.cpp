#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int incoming[2*100000 + 1];

int unknown[2*100000 + 1];
int edges[2*100000+1];

struct triple
{
    int fst;
    int snd;
    int trd;

    int& operator[](int x)
    {
        if(x == 0)
            return fst;
        if(x == 1)
            return snd;
        if(x == 2)
            return trd;
    }
};

int main()
{

    int n, m;
    cin >> n >> m;

    vector<map<int, triple>> graph(n+1);
    std::set<int> concluded;
    concluded.insert(1);
    for(int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        int dir = 1;
        if(y == 1)
        {
            dir = -1;
            swap(x, y);
        }
        graph[x].insert({y, {w, i, dir}});

        if(x == 1)
        {
            incoming[y] += w;
        }
        else
         {
            graph[y].insert({x, {w, i ,-dir}});
            unknown[x] += w;
            unknown[y] += w;
         }
    }
    std::set<int> start;
    for(int i = 2; i <= n; i++)
    {
        if(incoming[i] == unknown[i])
        {
            start.insert(i);
        }
    }

    while(!start.empty())
    {
        auto it = start.begin();
        int curr = *it;
        start.erase(it);
        for(auto jt : graph[curr])
        {
            incoming[jt.first] += jt.second.fst;
            unknown[jt.first] -= jt.second.fst;

            graph[jt.first].erase(curr);

            if(incoming[jt.first] == unknown[jt.first])
            {
                start.insert(jt.first);
            }
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(auto it :graph[i])
        {
            if(it.second.trd == -1)
            {
                edges[it.second.snd] = 1;
            }
        }
    }


    for(int i = 0; i < m; i++)
        cout << edges[i] << endl;


    return 0;
}

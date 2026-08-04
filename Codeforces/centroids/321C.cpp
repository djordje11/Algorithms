#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define N_MAX 100001
using ull = signed long long;

ull ch[N_MAX];

ull max_dist = 0;
ull max_node = 0;
set<int> set_path;
vector<int> path;
ull dist[N_MAX];
ull visited[N_MAX];
ull cnt[N_MAX];
bool deleted[N_MAX];
int parrent[N_MAX];
int command[N_MAX+1];
int dfs(int curr,int par, vector<vector<int>>& graph, vector<int> &path, int size)
{
    cnt[curr] = 1;
    parrent[curr] = par;
    path.push_back(curr);
    bool is_centroid = true;
    int ret = -1;

    for(auto it : graph[curr])
    {
        if(it != par && !deleted[it])
        {
            int res = dfs(it, curr,  graph, path, size);
            if(res != -1)
                ret = res;
            cnt[curr] += cnt[it];
            if(cnt[it] > size/2)
                is_centroid = false;
        }
    }
    if(is_centroid && size - cnt[curr] <= size/2)
    {
        ret = curr;
    }
    return ret;
}
int main()
{
    int n;
    cin >> n;

    vector<vector<int>> graph(n+1);
    map<pair<int, int>, int> edges;
    vector<int> distances(n+1);
    
    for(int i = 0; i < n-1; i++)
    {
        int x, y, w;
        cin >> x >> y;
        graph[x].push_back(y );
        graph[y].push_back(x);
    }

    vector<pair<int, pair<int, int>>> st;
    st.push_back({1, {n, 0}});

    ull sum = 0;
    while(st.size() > 0)
    {
        auto it = *(st.end()-1);
        st.pop_back();
        vector<int> path;

        if(it.second.first == 1)
        {
            deleted[it.first] = true;
            command[it.first] = it.second.second;
            continue;
        }
        
        int centroid = dfs(it.first, 0, graph, path, it.second.first);

        command[centroid] = it.second.second;


        deleted[centroid] = true;

        for(auto jt : graph[centroid])
        {
            if(!deleted[jt])
            {
                if(parrent[centroid] == jt)
                {
                    st.push_back({jt, {it.second.first - cnt[centroid], it.second.second+1}});
                }
                else
                {

                    st.push_back({jt, {cnt[jt], it.second.second+1}});
                }
            }
        }
    }

    for(int i = 1; i <= n; i++)
        cout << char('A' + command[i]) << " ";
    cout << endl; 

    return 0;
}

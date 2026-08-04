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

int distances[501];
int tmp_distances[501];

ull dfs2(int curr,int par, vector<vector<int>>& graph, int dist, int root, int k)
{
    ull sum = 0;
    if(curr == root)
    {
        for(int i = 0; i <= k; i++)
            distances[i] = tmp_distances[i] = 0;
    }
    else 
    {
        if(dist <= k)
            tmp_distances[dist]++;
        
        if(k-dist > 0)
            sum += distances[k-dist];
        if(k == dist)
            sum++;
    }
    for(auto it : graph[curr])
    {
        if(it != par && !deleted[it])
        {
            sum += dfs2(it, curr,  graph, dist+1, root, k);
            if(curr == root)
            {
                //sum += tmp_distances[k];
                for(int i = 0; i <= k; i++)
                {
                    distances[i] += tmp_distances[i];
                    tmp_distances[i] = 0;
                }
                
            }
        }
    }
    return sum;
}

int main()
{
    int n, k;
    cin >> n >> k;

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


    vector<pair<int, int>> st;
    st.push_back({1, n});

    ull sum = 0;
    while(st.size() > 0)
    {
        auto it = *(st.end()-1);
        st.pop_back();
        vector<int> path;

        if(it.second < k)
        {
            deleted[it.first] = true;
            continue;
        }
        
        int centroid = dfs(it.first, 0, graph, path, it.second);


        int ret = dfs2(centroid, 0, graph, 0, centroid, k);
        sum += ret;

        //cout << centroid << " " << ret << endl;

        deleted[centroid] = true;

        for(auto jt : graph[centroid])
        {
            if(!deleted[jt])
            {
                if(parrent[centroid] == jt)
                {
                    st.push_back({jt, it.second - cnt[centroid]});
                }
                else
                {

                    st.push_back({jt, cnt[jt]});
                }
            }
        }
    }
    cout << sum << endl;
    return 0;
}

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
int parrent_centroid[N_MAX+1];
int closest[N_MAX];

int dp[2 * 100000 + 1][22];
int t_in[2*100000 + 1];
int t_out[2*100000 + 1];
int tme = 0;
int depth[2*100000 + 1] = {-1};
int count[100001];
int all_count[100001];
int edges[100000];

int cls[100001][2];

void dfs_lca(int curr, int parr, vector<vector<int>>& graph)
{
    dp[curr][0] = parr;
    depth[curr] = 1 + depth[parr];
    t_in[curr] = tme++;
    for(auto it : graph[curr])
    {
        if(it != parr)
        {
            dfs_lca(it, curr, graph);
        }
    } 
    t_out[curr] = tme++;
}

bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}

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
int distance(int x, int y)
{
    if(x == y)
        return 0;
    if(is_ancestor(x, y) || is_ancestor(y, x))
        return std::abs(depth[x] - depth[y]);
    


    int anc = y;

    for(int i = 21; i >= 0; i--)
        if(dp[anc][i] != 0 && !is_ancestor(dp[anc][i], x))
            anc = dp[anc][i];
    
    anc = dp[anc][0];

    return depth[x] - depth[anc] + depth[y] - depth[anc];
}
void paint(int x)
{
    closest[x] = 0;
    int y = parrent_centroid[x];


    while(y != 0)
    {
        closest[y] = min(closest[y], distance(x, y));
        y = parrent_centroid[y];
    }
}

int closest_min(int x)
{
    int curr_min = closest[x];
    int y = parrent_centroid[x];

    while(y != 0)
    {
        curr_min = min(curr_min, distance(x, y) + closest[y]);
        y = parrent_centroid[y];
    }
    return curr_min;
}
int main()
{
    int n, m;
    cin >> n >> m;

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

    while(st.size() > 0)
    {
        auto it = *(st.end()-1);
        st.pop_back();
        vector<int> path;

        if(it.second.first == 1)
        {
            deleted[it.first] = true;
            parrent_centroid[it.first] = it.second.second;
            continue;
        }
        
        int centroid = dfs(it.first, 0, graph, path, it.second.first);

        command[centroid] = it.second.second;
        parrent_centroid[centroid] = it.second.second;

        deleted[centroid] = true;

        for(auto jt : graph[centroid])
        {
            if(!deleted[jt])
            {
                if(parrent[centroid] == jt)
                {
                    st.push_back({jt, {it.second.first - cnt[centroid], centroid}});
                }
                else
                {

                    st.push_back({jt, {cnt[jt], centroid}});
                }
            }
        }   
    }
    for(int i = 1; i <= n; i++)
    {
        closest[i] = N_MAX+10;
    }
    dfs_lca(1, 0, graph);
    for (int i = 1; i <= 21; i++)
        for (int j = 1; j <= n; j++)
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
    paint(1);
    for(int i = 1 ; i<= m; i++)
    {
        int t, v;
        cin >> t >> v;
        
        if(t == 1)
        {
            paint(v);
        }
        else {
            cout << closest_min(v) << "\n" ;
        }
    }
    return 0;
}

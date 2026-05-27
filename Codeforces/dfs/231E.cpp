#include <iostream>
#include <vector>


using namespace std;

#define N_MAX 100001

bool visited[N_MAX];
int t_in[2*N_MAX];
int t_out[2*N_MAX];
int num_of_cycle[N_MAX];
int t = 0;
bool top[N_MAX];
bool bot[N_MAX];
int stack[N_MAX];
int st_cnt = 0;
int dp[21][100000 + 1]; 
int depth[100000 + 1] = {-1};
int cycle_num[100000+1];
int cycle_curr = 1;
long long pw[N_MAX];

bool in_cycle[N_MAX];
#define MODUO 1000000007
int cnt = 0;


long long mul(long long x, long long y)
{
    return x * y >= MODUO ? (x*y)%MODUO : x*y; 
}
long long modpow(long long base, long long exp) {

    long long res = 1;
    int tmp = exp;
    if(base == 2)
        return pw[exp];
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % MODUO;

        base = (base * base) % MODUO;
        exp >>= 1;
    }

    //cout << res << " " << pw[tmp] << endl;
    return res;
}

void dfs1(int curr,int par, vector<vector<int>>& graph)
{
    visited[curr] = true;
    t_in[curr] = t++;
    stack[st_cnt++] = curr;

    dp[0][curr] = par;
    depth[curr] = 1 + depth[par];

    for(auto it : graph[curr])
    {
        if(it == par)continue;
        if(visited[it])
        {
            if(in_cycle[it])continue;
            bot[curr] = true;
            int i;
            for(i = st_cnt-1; i >= 0 && stack[i] != it; i--)
            {
                in_cycle[stack[i]] = true;
                cycle_num[stack[i]] = cycle_curr;
            }
            cycle_num[stack[i]] = cycle_curr++;
            in_cycle[stack[i]] = true;
            top[stack[i]] = true;
            continue;
        }

        dfs1(it, curr, graph);

    } 

    st_cnt--;
    t_out[curr] = t++;
}

void dfs2(int curr,int par, vector<vector<int>>& graph)
{
    visited[curr] = true;
    num_of_cycle[curr] = num_of_cycle[par];
    if(in_cycle[curr] && cycle_num[curr] != cycle_num[par])num_of_cycle[curr]++;
    for(auto it : graph[curr])
    {
        if(it == par || visited[it])continue;
        dfs2(it, curr, graph);
    } 
}

bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}
int path_to_ancestor(int x, int y)
{
    int cycles_y = num_of_cycle[y];
    int cycles_x = num_of_cycle[x];

    return modpow(2, cycles_y - cycles_x + in_cycle[x]);
    //return 1 << (cycles_y - cycles_x + in_cycle[x]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1);

    pw[0] = 1;

for (int i = 1; i < N_MAX; i++)
    pw[i] = (pw[i - 1] * 2) % MODUO;

    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs1(1, 0, graph);
    for(int i = 1; i <= n; i++)
        visited[i] = false;
    dfs2(1, 0, graph);


    for(int i = 1; 1<< i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[i][j] = dp[i-1][dp[i-1][j]];


    int q;
    cin >> q;

    for(int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        if(depth[x] > depth[y])
            swap(x, y);

        
        if(is_ancestor(x, y))
        {
            cout << path_to_ancestor(x, y) << "\n";
            continue;
        }

        int real_x = x;
        int real_y = y;
        int anc;
        if(!is_ancestor(x, y))
        {
            for(int i = 20; i >= 0; i--)
            {
                if(dp[i][x] != 0 && !is_ancestor(dp[i][x], real_y)) x = dp[i][x];
                if(dp[i][y] != 0 && !is_ancestor(dp[i][y], real_x)) y = dp[i][y];

            }
            anc = dp[0][x];
            //x = dp[0][x];
            
        }
        
        if(!in_cycle[anc])
        {
            cout << mul(path_to_ancestor(anc, real_x), path_to_ancestor(anc, real_y)) << "\n";
        }
        else if(bot[anc] || (in_cycle[anc] && cycle_num[anc] != cycle_num[x] && cycle_num[anc] != cycle_num[y]))
        {
            cout << mul(2, mul(modpow(2, num_of_cycle[real_x] - num_of_cycle[anc]), modpow(2, num_of_cycle[real_y] - num_of_cycle[anc]))) << "\n";
        }
        else if(cycle_num[anc] == cycle_num[x])
        {
            cout << mul(modpow(2, num_of_cycle[real_x] - num_of_cycle[anc] + 1), modpow(2, num_of_cycle[real_y] - num_of_cycle[anc])) << "\n";
        }
        else if(cycle_num[anc] == cycle_num[y])
        {
            cout << mul(modpow(2, num_of_cycle[real_x] - num_of_cycle[anc]), modpow(2, num_of_cycle[real_y] - num_of_cycle[anc] + 1)) << "\n";

        }
    }
    return 0;
}

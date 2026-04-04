#include <climits>
#include <iostream> 
#include <vector>
#include <cmath>

using namespace std;


template <int chunk_size>
struct seg_tree;

template <int chunk_size>
struct seg_tree_leaf;



template <int chunk_size>
struct seg_tree_interface
{
    virtual void add_value_to_each_element(int v, int l, int r) = 0;
    virtual void sum_interval(vector<int>&) = 0;

    static seg_tree_interface* create(int l, int r)
    {
        if (r - l <= chunk_size - 1)return new seg_tree_leaf<chunk_size>(l, r);

        return new seg_tree<chunk_size>(l, r);
    }
};


template <int chunk_size>
struct seg_tree : public seg_tree_interface<chunk_size>
{
    seg_tree_interface<chunk_size>* left = (nullptr), * right = nullptr;
    int m_l, m_r, m;
    int value = 1;
    seg_tree(int l, int r)
    {
        this->m_l = l;
        this->m_r = r;
        m = (r + l) / 2;

        if (r - l <= chunk_size - 1)
        {
            return;
        }

        left = seg_tree_interface<chunk_size>::create(l, m);
        right = seg_tree_interface<chunk_size>::create(m + 1, r);
    }

    void add_value_to_each_element(int v, int l, int r) override
    {
        if (l > m_r || r < m_l || value == 0 || l > r)return;
        

        if (l <= m_l && r >= m_r)
        {
            value += v;
            return;
        }
        else if (l > m)
        {
            right->add_value_to_each_element(v, l, r);
        }
        else if (r <= m)
        {
            left->add_value_to_each_element(v, l, r);
        }
        else
        {
            right->add_value_to_each_element(v, l, r);
            left->add_value_to_each_element(v, l, r);
        }
    }

    void sum_interval(vector<int>& rets) override
    {
        if(value == 0)
        {
            for(int i = m_l; i < m_r; i++)
                rets[i] = 0;
            return ;
        }
        right->sum_interval(rets);
        left->sum_interval(rets);
    }
};

template <int chunk_size>
struct seg_tree_leaf : public seg_tree_interface<chunk_size>
{
    int w[chunk_size];
    int m_l, m_r;
    seg_tree_leaf(int l, int r)
    {
        m_l = l;
        m_r = r;
        for (int i = l; i <= r; i++)
        {
            w[i - l] = 1;
        }
    }
    void add_value_to_each_element(int v, int l, int r) override
    {
        if(l > r)return;
        for (int i = m_l; i <= m_r; i++)
        {
            if (i >= l && i <= r && w[i-m_l] != 0)
            {
                w[i - m_l] += v;
            }
        }
    }

    void sum_interval(vector<int>& rets) override
    {
        for (int i = m_l; i <= m_r; i++)
        {
            rets[i] = w[i - m_l];
            
        }
    }
};


int tmp[100000 + 1];
int t = 0;
int initial_sum[100000+1];
int node_maps[100000 + 1][2];
int parent[100001];
bool edge_in_mst[200001];
int edges[200001][2];
int ind = 0;
int t_in[2 * 100000 + 1];
int t_out[2 * 100000 + 1];
int depth[2 * 100000 + 1];
int dp[2 * 100000 + 1][22];

bool is_ancestor(int x, int y)
{
    return t_in[x] < t_in[y] && t_out[x] > t_out[y];
}
void dfs(int curr, std::vector<std::vector<int>>& graph, int parr, int curr_depth)
{
    dp[curr][0] = parr;
    node_maps[curr][0] = ind++;
    depth[curr] = curr_depth;
    t_in[curr] = t++;
    for (auto it : graph[curr])
    {
        if (it != parr)
        {
            dfs(it, graph, curr, curr_depth+1);
        }
    }
    t_out[curr] = t++;
    node_maps[curr][1] = ind++;
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

    vector<vector<int>> graph(n + 1);
    vector<vector<int>> mst_graph(n + 1);
    

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
        edge_in_mst[i] = dsu(x, y);
        if(edge_in_mst[i])
        {
            mst_graph[x].push_back(y);
            mst_graph[y].push_back(x);
        }
        edges[i][0] = x;
        edges[i][1] = y;
    }

    dfs(1, mst_graph, 0, 0);

    for (int i = 1; i <= 21; i++)
        for (int j = 1; j <= n; j++)
            dp[j][i] = dp[dp[j][i - 1]][i - 1];

    seg_tree_interface<5>* s = seg_tree_interface<5>::create(0, 2*n-1);

    for(int i = 0; i < m; i++)
    {
        if(edge_in_mst[i])continue;
        int x = edges[i][0];
        int y = edges[i][1];

        if(depth[y] < depth[x])
            swap(x, y);

        if(is_ancestor(x, y))
        {
            int anc = y;
            for(int i = 21; i >= 0; i--)
                if(dp[anc][i] != 0 && is_ancestor(x, dp[anc][i]))
                    anc = dp[anc][i];
            // node_maps[anc][0] ----node_maps[y][0] - 1;
            // node_maps[y][1] + 1 ---- node_maps[anc][1]
            s->add_value_to_each_element(-1, node_maps[anc][0], node_maps[y][0] - 1);
            s->add_value_to_each_element(-1, node_maps[y][1] + 1, node_maps[anc][1]);
        }
        else 
        {
            if(node_maps[x][0] > node_maps[y][0])
                swap(x, y);

            s->add_value_to_each_element(-1, node_maps[1][0], node_maps[x][0] - 1);
            s->add_value_to_each_element(-1, node_maps[x][1] + 1, node_maps[y][0] - 1);
            s->add_value_to_each_element(-1, node_maps[y][1] + 1, node_maps[1][1]);
        }
    }


    vector<int> res(2 * n);

    s->sum_interval(res);

    for(int i = 1; i <= n; i++)
    {
        cout << res[node_maps[i][0]];
    }
    cout << endl;


    return 0;
}

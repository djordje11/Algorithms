//not finished


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
    int sum = 0;
    virtual void add_value_to_each_element(int v, int l, int r) = 0;
    virtual int sum_interval(int l, int r) = 0;

    static seg_tree_interface* create(int l, int r, vector<int>& nums)
    {
        if (r - l <= chunk_size - 1)return new seg_tree_leaf<chunk_size>(l, r, nums);

        return new seg_tree<chunk_size>(l, r, nums);
    }
};


template <int chunk_size>
struct seg_tree : public seg_tree_interface<chunk_size>
{
    seg_tree_interface<chunk_size>* left = (nullptr), * right = nullptr;
    int m_l, m_r, m;
    int value = 0;
    seg_tree(int l, int r, vector<int>& nums)
    {
        this->m_l = l;
        this->m_r = r;
        m = (r + l) / 2;

        if (r - l <= chunk_size - 1)
        {
            return;
        }

        left = seg_tree_interface<chunk_size>::create(l, m, nums);
        right = seg_tree_interface<chunk_size>::create(m + 1, r, nums);
        this->sum = left->sum + right->sum;
    }

    void add_value_to_each_element(int v, int l, int r) override
    {
        if (l > m_r || r < m_l)return;


        if (l <= m_l && r >= m_r)
        {
            value += v;
            this->sum += (m_r - m_l + 1) * v;
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
        this->sum = left->sum + right->sum + (m_r - m_l + 1) * value;
    }

    int sum_interval(int l, int r) override
    {
        if (l > m_r || r < m_l)return 0;

        if (l <= m_l && r >= m_r)
        {
            return this->sum;
        }
        else if (l > m)
        {
            return right->sum_interval(l, r) + (std::min(m_r, r) - l + 1) * value;
        }
        else if (r <= m)
        {
            return left->sum_interval(l, r) + (r - std::max(l, m_l) + 1) * value;
        }
        else
        {
            return right->sum_interval(l, r) + (std::min(m_r, r) - m) * value
                + left->sum_interval(l, r) + (m - std::max(l, m_l) + 1) * value;
        }
    }
};

template <int chunk_size>
struct seg_tree_leaf : public seg_tree_interface<chunk_size>
{
    int w[chunk_size];
    int m_l, m_r;
    seg_tree_leaf(int l, int r, vector<int>& nums)
    {
        m_l = l;
        m_r = r;
        for (int i = l; i <= r; i++)
        {
            this->sum += nums[i];
            w[i - l] = nums[i];
        }
    }
    void add_value_to_each_element(int v, int l, int r) override
    {
        for (int i = m_l; i <= m_r; i++)
        {
            if (i >= l && i <= r)
            {
                w[i - m_l] += v;
                this->sum += v;
            }
        }
    }

    int sum_interval(int l, int r) override
    {
        if (l > m_r || r < m_l)return 0;

        int ret = 0;
        for (int i = m_l; i <= m_r; i++)
        {
            if (i >= l && i <= r)
            {
                ret += w[i - m_l];
            }
        }
        return ret;
    }
};


int dp[100000 + 1][22];
int t_in[100000 + 1];
int t_out[100000 + 1];
int qs[100000 + 1];
int depth[100000 + 1];
int tmp[100000 + 1];
int t = 0;
int initial_sum[100000+1];
int node_maps[100000 + 1][2];
int ind = 0;

void dfs(int curr, std::vector<std::vector<int>>& graph, vector<int>& visited, int parr, int curr_depth, vector<int>& nums)
{
    dp[curr][0] = parr;
    depth[curr] = curr_depth;
    t_in[curr] = t++;
    visited[curr] = true;
    nums[ind] = initial_sum[curr];
    node_maps[curr][0] = ind++;
    for (auto it : graph[curr])
    {
        if (!visited[it])
        {
            dfs(it, graph, visited, curr, curr_depth + 1, nums);
           // initial_sum[curr] += initial_sum[it];
        }
    }


    nums[ind] = initial_sum[curr];
    node_maps[curr][1] = ind++;
    t_out[curr] = t++;
}

bool is_ancestor(int x, int y)
{
    return t_in[x] < t_in[y] && t_out[x] > t_out[y];
}

int lca(int x, int y)
{
    if (x == y)
        return x;
    if (is_ancestor(x, y))
        return x;

    if (is_ancestor(y, x))
        return y;

    int anc = y;

    for (int i = 21; i >= 0; i--)
        if (dp[anc][i] != 0 && !is_ancestor(dp[anc][i], x))
            anc = dp[anc][i];

    anc = dp[anc][0];

    return anc;
}



int main()
{

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<int> nums(2 * n);
    
    for (int i = 1; i <= n; i++)
        cin >> initial_sum[i];

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    t_out[0] = INT_MAX;
    vector<int> visited(n + 1);
  dfs(1, graph, visited, 0, 0, nums);

    seg_tree_interface<5>* s = seg_tree_interface<5>::create(0, 2 * n - 1, nums);


    for (int i = 1; i <= 21; i++)
        for (int j = 1; j <= n; j++)
            dp[j][i] = dp[dp[j][i - 1]][i - 1];

    int current_root = 1;

    for (int i = 0; i < m; i++)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            int v;
            cin >> v;
            current_root = v;
        }
        else if (t == 2)
        {
            int u, v, x;
            cin >> u >> v >> x;

            if (is_ancestor(current_root, u) && is_ancestor(current_root, v))
            {
                int anc = lca(u, v);
                if(anc == current_root)
                    s->add_value_to_each_element(x, node_maps[1][0], node_maps[1][1]);
                else
                    s->add_value_to_each_element(x, node_maps[anc][0], node_maps[anc][1]);
                
            }
            else if (is_ancestor(current_root, u) || is_ancestor(current_root, v))
            {
                s->add_value_to_each_element(x, node_maps[1][0], node_maps[1][1]);
            }
            else
            {

                s->add_value_to_each_element(x, node_maps[1][0], node_maps[1][1]);

                int anc = current_root;
                for (int i = 21; i >= 0; i--)
                    if (dp[anc][i] != 0 && !is_ancestor(dp[anc][i], u) && !is_ancestor(dp[anc][i], v) && dp[anc][i] != u && dp[anc][i] != v)
                        anc = dp[anc][i];


                s->add_value_to_each_element(-x, node_maps[anc][0], node_maps[anc][1]);
            }

        }
        else if (t == 3)
        {
            int v;
            cin >> v;
            if (is_ancestor(current_root, v) || !is_ancestor(v, current_root))
                cout << s->sum_interval(node_maps[v][0], node_maps[v][1]) / 2 << endl;
            else
            {
                int anc = current_root;

                for (int i = 21; i >= 0; i--)
                    if (dp[anc][i] != 0 && !is_ancestor(dp[anc][i], v) && dp[anc][i] != v)
                        anc = dp[anc][i];

                cout << (s->sum_interval(node_maps[1][0], node_maps[1][1]) - s->sum_interval(node_maps[anc][0], node_maps[anc][1])) / 2 << endl;

            }
        }


    }



    return 0;
}

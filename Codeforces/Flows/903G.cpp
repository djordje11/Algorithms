#include <iostream>

using namespace std;

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
    int long long sum = 0;
    int long long min = INT_MAX;
    virtual void add_value_to_each_element(int long long v, int long long l, int long long r) = 0;
    virtual int long long sum_interval(int long long l, int long long r) = 0;
    virtual int long long find_min(int long long l, int long long r) = 0;

    static seg_tree_interface* create(int long long l, int long long r, vector<int long long>& nums)
    {
        if (r - l <= chunk_size - 1)return new seg_tree_leaf<chunk_size>(l, r, nums);

        return new seg_tree<chunk_size>(l, r, nums);
    }
    virtual void print() = 0;
};


template <int chunk_size>
struct seg_tree : public seg_tree_interface<chunk_size>
{
    seg_tree_interface<chunk_size>* left = (nullptr), * right = nullptr;
    int long long m_l, m_r, m;
    int long long value = 0;
    seg_tree(int long long l, int long long r, vector<int long long>& nums)
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
        this->min = std::min(left->min, right->min);
    }

    void add_value_to_each_element(int long long v, int long long l, int long long r) override
    {
        if (l > m_r || r < m_l)return;


        if (l <= m_l && r >= m_r)
        {
            value += v;
            this->sum += (m_r - m_l + 1) * v;
            this->min += v;
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
        this->min = std::min(right->min + value, left->min + value);
        this->sum = left->sum + right->sum + (m_r - m_l + 1) * value;
    }
    int long long find_min(int long long l, int long long r) override
    {
        if (l > m_r || r < m_l)return INT_MAX;
        
        if (l <= m_l && r >= m_r)
        {
            return this->min;
        }
        else if (l > m)
        {
            return value + right->find_min(l, r);
        }
        else if (r <= m)
        {
            return value + left->find_min(l, r);
        }
        else
        {
            return value + min(left->find_min(l, r), right->find_min(l, r));
        }

    }
    int long long sum_interval(int long long l, int long long r) override
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
    void print() override
    {
        left->print();
        right->print();
    }
};

template <int chunk_size>
struct seg_tree_leaf : public seg_tree_interface<chunk_size>
{
    int long long w[chunk_size];
    int long long m_l, m_r;
    void print() override
    {
        for(int i = m_l; i <= m_r; i++)
            cout << w[i-m_l] << " ";

    }
    seg_tree_leaf(int long long l, int long long r, vector<int long long>& nums)
    {
        m_l = l;
        m_r = r;
        for (int i = l; i <= r; i++)
        {
            this->sum += nums[i];
            this->min = std::min(this->min, nums[i]);
            w[i - l] = nums[i];
        }
    }
    void add_value_to_each_element(int long long v, int long long l, int long long r) override
    {
        int long long new_min = INT_MAX;
        for (int i = m_l; i <= m_r; i++)
        {
            if (i >= l && i <= r)
            {
                w[i - m_l] += v;
                this->sum += v;
            }
            new_min = std::min<int long long>(w[i-m_l], new_min);
        }
        this->min = new_min;
    }

    int long long find_min(int long long l, int long long r) override
    {
        int long long min_ret = INT_MAX;
        for(int i = m_l; i <= m_r; i++)
        {
            if(i >= l && i <= r)
            {
                min_ret = std::min<int long long>(min_ret, w[i-m_l]);
            }
        }
        return min_ret;
    }
    int long long sum_interval(int long long l, int long long r) override
    {
        if (l > m_r || r < m_l)return 0;

        int long long ret = 0;
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

#define SEG_LEAF_SIZE 5

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<int long long> a(n), b(n);
    vector<vector<pair<int long long, int long long>>> graph(n);
    for(int i = 0; i <= n-2; i++)
    {
        cin >> a[i] >> b[i];
    }

    a[n-1] = 0;
    seg_tree_interface<SEG_LEAF_SIZE>* s = seg_tree_interface<SEG_LEAF_SIZE>::create(0, n - 2, b);

    for(int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        graph[x-1].push_back({y-1, w});
    }

    int long long sum_to_last = 0;
    int long long a_to_b = 0;
    vector<int long long> other;

    for(int i = 0; i <= n-1; i++)
    {
        int long long only_a = a[i];
        for(auto it : graph[i])
        {
            if(it.first == n-1)
            {
                sum_to_last += it.second;
            }
            else
            {
                a_to_b += it.second;
                only_a += it.second;
                s->add_value_to_each_element(-it.second, it.first, n-2);
            }
        }
        other.push_back(min<int long long>(a[i] + a_to_b + sum_to_last, a[i] + a_to_b + s->find_min(0, n-2 ) + sum_to_last));
    }    
    seg_tree_interface<SEG_LEAF_SIZE>* s_other = seg_tree_interface<SEG_LEAF_SIZE>::create(0, n - 1, other);

    cout << s_other->min << endl;

    for(int i = 0; i < q; i++)
    {
        int long long x, w;
        cin >> x >> w;
        x--;
        s_other->add_value_to_each_element(w - a[x], x, x);
        a[x] = w;
        cout << s_other->min << endl;
    }

    return 0;
}

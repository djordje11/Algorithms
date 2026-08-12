#include <iostream>

using namespace std;

#include <climits>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define S 0
#define T 1

template <int chunk_size>
struct seg_tree;

template <int chunk_size>
struct seg_tree_leaf;

using ull = unsigned long long;

template <int chunk_size>
struct seg_tree_interface
{
    virtual void add_value_to_each_element(ull a, ull b, ull c, ull l, ull r) = 0;
    virtual void compute() = 0;
    ull dp[2][2];

    ull min()
    {
        ull curr = ull(1) << 63;
        for (int i = 0; i <= 1; i++)
            for (int j = 0; j <= 1; j++)
                curr = ::min(dp[i][j], curr);
        return curr;
    }

    static seg_tree_interface* create(ull l, ull r, vector<ull>& a, vector<ull>& b, vector<ull>& c)
    {
        if (r - l <= chunk_size - 1)return new seg_tree_leaf<chunk_size>(l, r, a, b, c);

        return new seg_tree<chunk_size>(l, r, a, b, c);
    }
    virtual void print() = 0;
};


template <int chunk_size>
struct seg_tree : public seg_tree_interface<chunk_size>
{
    seg_tree_interface<chunk_size>* left = (nullptr), * right = nullptr;
    ull m_l, m_r, m;
    ull cc = 0;
    ull value = 0;
    seg_tree(ull l, ull r, vector<ull>& a, vector<ull>& b, vector<ull>& c)
    {
        this->m_l = l;
        this->m_r = r;
        m = (r + l) / 2;
        cc = c[m];

        left = seg_tree_interface<chunk_size>::create(l, m, a, b, c);
        right = seg_tree_interface<chunk_size>::create(m + 1, r, a, b, c);
        compute();
    }
    void compute()
    {
        for (int i = S; i <= T; i++)
        {
            for (int j = S; j <= T; j++)
            {
                this->dp[i][j] = left->dp[i][i] + right->dp[j][j] + (i == S && j == T ? cc : 0);
                for (int k = S; k <= T; k++)
                {
                    for (int z = S; z <= T; z++)
                    {
                        if (left->dp[i][k] != -1 && right->dp[z][j] != -1)
                        {
                            this->dp[i][j] = min(this->dp[i][j], left->dp[i][k] + right->dp[z][j] + (k == S && z == T ? cc : 0));
                        }
                    }
                }
            }
        }
    }
    void add_value_to_each_element(ull a, ull b, ull c, ull l, ull r)override
    {
        if (l > m_r || r < m_l)return;

        if (l == m)
            cc = c;

        if (l <= m_l && r >= m_r)
        {
            return;
        }
        else if (l > m)
        {
            right->add_value_to_each_element(a, b, c, l, r);
        }
        else if (r <= m)
        {
            left->add_value_to_each_element(a, b, c, l, r);
        }
        else
        {
            right->add_value_to_each_element(a, b, c, l, r);
            left->add_value_to_each_element(a, b, c, l, r);
        }
        compute();
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
    ull aa[chunk_size];
    ull bb[chunk_size];
    ull cc[chunk_size];
    ull m_l, m_r;
    void print() override
    {
        for (int i = m_l; i <= m_r; i++)
            cout << aa[i - m_l] << " ";

    }
    seg_tree_leaf(ull l, ull r, vector<ull>& a, vector<ull>& b, vector<ull>& c)
    {
        m_l = l;
        m_r = r;
        for (int i = l; i <= r; i++)
        {
            aa[i - l] = a[i];
            bb[i - l] = b[i];
            if (i < c.size())
                cc[i - l] = c[i];
        }
        compute();
    }

    void compute()
    {
        if (m_r > m_l)
        {
            this->dp[S][T] = bb[0] + cc[0] + aa[1];
            this->dp[T][S] = aa[0] + bb[1];

            this->dp[S][S] = bb[0] + bb[1];
            this->dp[T][T] = aa[0] + aa[1];
        }
        else
        {
            this->dp[S][S] = bb[0];
            this->dp[T][T] = aa[0];
            this->dp[T][S] = this->dp[S][T] = -1;
        }
        
    }
    void add_value_to_each_element(ull a, ull b, ull c, ull l, ull r) override
    {
        aa[l - m_l] = a;
        bb[l - m_l] = b;
        cc[l - m_l] = c;
        compute();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<ull> a(n), b(n), c(n-1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    for (int i = 0; i < n-1; i++)
        cin >> c[i];

    seg_tree_interface<2>* s = seg_tree_interface<2>::create(0, a.size() - 1, a, b, c);

    for (int i = 0; i < m; i++)
    {
        ull dest, x, y, z;
        cin >> dest >> x >> y >> z;
        dest--;
        s->add_value_to_each_element(x, y, z, dest, dest);
        cout << s->min() << "\n";
    }
  
    return 0;
}

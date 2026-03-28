#include <iostream>
#include <vector>
#include <set>
 #include <algorithm>
using namespace std;
int dp[21][100000 + 1];
int t_in[100000 + 1];
int t_out[100000 + 1];
int tme = 0;
int depth[100000 + 1] = { -1 };
int pwp[100000 + 1];
int num_of_people[100001];
 
 
#include <iostream>
 
struct moj_set
{
    int size = 0;
    int arr[10];
 
    void insert(int node)
    {
        int max1 = 0;
        int max_pos = 0;
        for (int i = 0; i < size; i++)
        {    
            if (arr[i] > max1)
            {
                max1 = arr[i];
                max_pos = i;
            }
            if(node == arr[i])return;
        }
        if(size == 10)
        {
            if(arr[max_pos] > node)
                arr[max_pos] = node;
        }
        else
        {
            arr[size++] = node;
        }
    }
 
    // Iterator class
    class iterator
    {
    private:
        int* ptr;
 
    public:
        iterator(int* p) : ptr(p) {}
 
        // Dereference operator
        int& operator*() { return *ptr; }
 
        // Pre-increment operator
        iterator& operator++()
        {
            ++ptr;
            return *this;
        }
 
        // Equality comparison operator
        bool operator!=(const iterator& other) const
        {
            return ptr != other.ptr;
        }
    };
 
    // Methods to return iterators
    iterator begin()
    {
        return iterator(arr);
    }
 
    iterator end()
    {
        return iterator(arr + size);
    }
};
moj_set dp_p[21][100000+1];
 
 
void dfs(int curr, int parr, vector<vector<int>>& graph, vector<set<int>>& people)
{
    dp[0][curr] = parr;
    depth[curr] = 1 + depth[parr];
    t_in[curr] = tme++;
    num_of_people[curr] = num_of_people[parr] + people[curr].size();
 
    for(auto it : people[curr])
    {
        dp_p[0][curr].insert(it);
        if(dp_p[0][curr].size == 10)
            break;
    }
    int s = 0;
    for(auto it : people[parr])
    {
        if(s == 10)break;
        dp_p[0][curr].insert(it);
        s++;
    }
 
    if (people[parr].size() != 0)
        pwp[curr] = parr;
    else
        pwp[curr] = pwp[parr];
 
    for (auto it : graph[curr])
    {
        if (it != parr)
        {
            dfs(it, curr, graph, people);
        }
    }
    t_out[curr] = tme++;
}
 
 
bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}
#include <algorithm>
//int p[100000], p_count = 0;
//int p_rev[100000], p_rev_count = 0;
int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> graph(n + 1);
    vector<set<int>> people(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[y].push_back(x);
        graph[x].push_back(y);
    }
    
 
 
    
   
    for (int i = 1; i <= m; i++)
    {
        int c;
        cin >> c;
        if(people[c].size() < 10)
            people[c].insert(i);
    }
    dfs(1, 0, graph, people);
    for (int i = 1; 1 << i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
    }
 
    for (int i = 1; 1 << i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for(auto it : dp_p[i-1][j])
                dp_p[i][j].insert(it);
            
            for(auto it : dp_p[i-1][dp[i-1][j]])
                dp_p[i][j].insert(it);
            
        }
    }
 
    while (q--)
    {
        int x, y, a;
        cin >> x >> y >> a;
        
        
 
        if(depth[x] > depth[y])
            std::swap(x, y);
        
 
        std::set<int> curr_min;
        for(int i = 20; i >= 0; i--)
            if(dp[i][x] != 0 && !is_ancestor(dp[i][x], y))
            { 
                for(auto it : dp_p[i][x])
                {
                    curr_min.insert(it);
                    if(curr_min.size() > 10 )
                    {
                        curr_min.erase(--curr_min.end());
                    }
                }
                x = dp[i][x];
            }
 
        if(!is_ancestor(x, y) && x != y)
        {
            for(auto it : dp_p[0][x])
            {
                curr_min.insert(it);
                if(curr_min.size() > 10 )
                {
                    curr_min.erase(--curr_min.end());
                }
            }
            x = dp[0][x];
        }
 
        for(int i = 20; i >= 0; i--)
            if(dp[i][y] != 0 && y != x && !is_ancestor(dp[i][y], x))
            {
                for(auto it : dp_p[i][y])
                {
                    curr_min.insert(it);
                    if(curr_min.size() > 10 )
                    {
                        curr_min.erase(--curr_min.end());
                    }
                }
                y = dp[i][y];
            }
        
        if(x == y)
        {
            for(auto it : people[y])
            {
                curr_min.insert(it);
                if(curr_min.size() > 10 )
                {
                    curr_min.erase(--curr_min.end());
                }
            }
        }
        else
        {
            for(auto it : dp_p[0][y])
            {
                curr_min.insert(it);
                if(curr_min.size() > 10 )
                {
                    curr_min.erase(--curr_min.end());
                }
            }
        }
        auto it  = curr_min.begin(); 
        cout << std::min(a, int(curr_min.size())) << " ";
        for(int i = 0; i< std::min(a, int(curr_min.size())); i++)
        {
            cout << *it++ << " ";
        }
        cout << endl;
    }
 
 
    return 0;
}
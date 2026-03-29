#include <vector>
#include <iostream>

using ull = unsigned long long;
using namespace std;

ull dp_r[200001];
ull dp_inv[200001];
ull dp_tmp[200001];

ull moduo = 1000000007;
vector<vector<ull>> dp;

ull mul(ull x, ull y)
{
    return x * y >= moduo ? (x*y)% moduo : x*y; 
}
ull add(ull x, ull y)
{
    return x + y >= moduo ? (x+y)% moduo : x+y; 
}

ull bin_exp(ull a, ull b) {
    if (b == 0) {
        return 1ULL;
    }
    if (b % 2) {
        return bin_exp(a, b - 1) * 1ULL * a % moduo;
    }
    ull res = bin_exp(a, b / 2);
    return res * 1ULL * res % moduo;
}

ull inv(ull a) {
    return bin_exp(a, moduo - 2);
}


void dfs(vector<vector<int>>& graph, int curr, int par)
{    
    int childs = graph[curr].size() - (par == 0 ?  0 : 1);
    dp_tmp[curr] = dp_r[curr] = 1;
    dp[curr] = vector<ull>(childs + 1);
    int count = 0, pos = -1;
    int i = 1;
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            dfs(graph, it, curr);

            if(add(1, dp_r[it]) == 0ULL)
            {
                count++;
                pos = i;
            }
            else 
            {
                dp_tmp[curr] = mul(dp_tmp[curr], add(1, dp_r[it]));
            }
            dp_r[curr] = mul(dp_r[curr], add(1, dp_r[it]));
            i++;
        }
    }
    i = 1;
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            if(count >= 2)
            {
                dp[curr][i] = 0;
            }
            else if(count == 1)
            {
                if(i == pos)
                    dp[curr][i] = dp_tmp[curr];
                else
                    dp[curr][i] = 0;
            }
            else if( count == 0)
            {
                dp[curr][i] = mul(dp_r[curr] , inv(add(1, dp_r[it])));
            }
            i++;
        }
    }
}

void dfs2(vector<vector<int>>& graph, int curr, int par, ull prev)
{    

    int i = 1; 
    dp_inv[curr] = prev;
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            dfs2(graph, it, curr, add(mul(prev, dp[curr][i]), 1));
            i++;
        }
    }
}



int main()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n+1);
    dp = vector<vector<ull>>(n+1);
    for(int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;
        graph[i].push_back(p);
        graph[p].push_back(i);
    }

    dfs(graph, 1, 0);
    dfs2(graph, 1, 0, 1);

    for(int i = 1; i<= n; i++)
        cout << mul(dp_r[i], dp_inv[i]) << " ";
    cout << endl;
    return 0;
}
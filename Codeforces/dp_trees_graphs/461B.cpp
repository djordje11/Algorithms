#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool colors[100001];

unsigned long long dp[100001][2];
unsigned long long moduo = 1000000007;

unsigned long long mul(unsigned long long x, unsigned long long y)
{
    return x * y >= moduo ? (x*y)% moduo : x*y; 
}
unsigned long long add(unsigned long long x, unsigned long long y)
{
    return x + y >= moduo ? (x+y)% moduo : x+y; 
}


unsigned long long bin_exp(unsigned long long a, unsigned long long b) {
    if (b == 0) {
        return 1ULL;
    }
    if (b % 2) {
        return bin_exp(a, b - 1) * 1ULL * a % moduo;
    }
    unsigned long long res = bin_exp(a, b / 2);
    return res * 1ULL * res % moduo;
}

unsigned long long inv(unsigned long long a) {
    return bin_exp(a, moduo - 2);
}

void dfs(vector<vector<int>>& graph, int curr, int par)
{
    
    if(colors[curr] == 0)
    {
        dp[curr][0] = 1;
        dp[curr][1] = 0;
    }
    else 
    {
        dp[curr][0] = 0;
        dp[curr][1] = 1;
    }    
    

    bool leaf = true;
    unsigned long long p_all = 1;
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            leaf = false;
            dfs(graph, it, curr);
            if(colors[curr] == 0)
            {
                dp[curr][0] = mul(dp[curr][0], add(dp[it][0], dp[it][1]));
            }
            p_all = mul(p_all, add(dp[it][0],dp[it][1]));
        }
    }

    if(!leaf)
    {
        if(colors[curr])
        {
            dp[curr][1] = p_all;
        }
        else 
        {
            for(auto it : graph[curr])
            {
                if(it != par)
                {
                    dp[curr][1] = add(dp[curr][1], mul(mul(dp[it][1], p_all), inv(add(dp[it][0], dp[it][1]))));
                }
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> graph(n+1);

    for(int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;
        graph[i].push_back(p+1);
        graph[p+1].push_back(i);
    }

    for(int i = 1; i <= n; i++)
        cin >> colors[i];


    dfs(graph, 1, -1);

    cout << dp[1][1] << endl;


    return 0;
}
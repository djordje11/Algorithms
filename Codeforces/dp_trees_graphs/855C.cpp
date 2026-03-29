#include <climits>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
using ull = unsigned long long ;

const int max_n = 100001;
const ull moduo = 1000000007;
int parents[max_n];
int childs[max_n];

int n, m;
int k, x;

unsigned long long mul(unsigned long long x, unsigned long long y)
{
    return x * y >= moduo ? (x*y)% moduo : x*y; 
}
unsigned long long add(unsigned long long x, unsigned long long y)
{
    return x + y >= moduo ? (x+y)% moduo : x+y; 
}
struct num
{
    ull x;
    num operator+(const num& w)
    {
        return {add(x, w.x)};
    }
    num operator*(const num& w)
    {
        return {mul(x, w.x)};
    }
    
};
struct triple
{
    num fst;
    num snd;
    num trd;

    num& operator[](int x)
    {
        if(x == 0)
            return fst;
        if(x == 1)
            return snd;
        if(x == 2)
            return trd;
    }
};

vector<std::vector<triple>> dp[max_n];
vector<int> cnt[max_n];



void init_dfs(vector<vector<int>>& graph, int curr, int par)
{
    childs[curr] = graph[curr].size() - (par == 0 ?  0 : 1);
    parents[curr] = par;

    cnt[curr] = vector<int>(childs[curr] + 1, 0);
    int i = 1;
    cnt[curr][0] = 1;

    dp[curr] = vector<std::vector<triple>>(childs[curr]+ 1, std::vector<triple>(11, {0, 0, 0}));


    for(auto it : graph[curr])
    {
        if(it != par)
        {
            init_dfs(graph, it, curr);
            cnt[curr][i] = cnt[curr][i-1] + cnt[it][childs[it]];
            i++;
        }

    }

}

void dfs(vector<vector<int>>& graph, int curr, int par)
{
    int i = 1;
    

    if(x == 0)
    {
        dp[curr][0][0][0] = {ull(1)};
        dp[curr][0][0][1] = {ull(0)};
        dp[curr][0][0][2] = {ull(0)};
    }
    else if(x == 1)
    {
        dp[curr][0][x][0] = {0};
        dp[curr][0][x][1] = {1}; 
        dp[curr][0][x][2] = {0};
    }
    else if(x > 1)
    {
        dp[curr][0][x][1] = {0}; 
        dp[curr][0][x][2] = {0};
        dp[curr][0][x][0] = {0};
    }
    
    for(auto it : graph[curr])
    {
        if(it != par)
        {
            dfs(graph, it, curr);


            for(int j = 0; j <= x; j++)
            {
                dp[curr][i][x][0] = dp[curr][i][x][0] 
                                    + dp[curr][i-1][j][0]*(dp[it][childs[it]][x-j][0]*num{ull(m-1)} + dp[it][childs[it]][x-j][2]);

                dp[curr][i][x][1] = dp[curr][i][x][1]
                                    + dp[curr][i-1][j][1]*(dp[it][childs[it]][x-j][0]*num{ull(k-1)} + dp[it][childs[it]][x-j][2]);
                
                dp[curr][i][x][2] = dp[curr][i][x][2]
                                    + dp[curr][i-1][j][2]*(dp[it][childs[it]][x-j][0]*num{ull(m-1)} + dp[it][childs[it]][x-j][2] + dp[it][childs[it]][x-j][1]);

                dp[curr][i][x][2] = dp[curr][i][x][2] + dp[curr][i-1][j][0]*num{ull(k-1)}*dp[it][childs[it]][x-j][1];                
            }
            i++;
        }
    }
}


int main()
{
    cin >> n >> m;

    vector<vector<int>> graph(n+1);

    for(int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int pom;
    cin >> k >> pom;    


    vector<ull> exp(n+1);

    exp[0] = 1;
    for(int i = 1; i <= n; i++)
    {
        exp[i] = mul(exp[i-1], (m-1));
    }


    ull sum = 0;
    init_dfs(graph, 1, 0);

    for(x = 0; x <= pom; x++)
    {
        dfs(graph, 1, 0);
        ull tmp = 0;

        tmp = (num{ull(m-1)}*dp[1][childs[1]][x][0] + dp[1][childs[1]][x][1] + dp[1][childs[1]][x][2]).x;

        //cout << "x == " << x << " --> " << tmp << endl;
        sum = add(sum , tmp);

    }


    cout << sum << endl;
    return 0;
}